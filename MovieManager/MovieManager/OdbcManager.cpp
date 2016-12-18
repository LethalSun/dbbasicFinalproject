#include "stdafx.h"
#include "OdbcManager.h"
#include <stdio.h>
//생성자
OdbcManager::OdbcManager()
	:
	returnVal(SQL_SUCCESS)
{
	//환경 핸들을 할당하고 버전 속성을 설정한다.
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
}
//파괴자
OdbcManager::~OdbcManager()
{
	if (hStmt)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	if (hDbcon)
	{
		SQLDisconnect(hDbcon);
	}
	if (hDbcon)
	{
		SQLFreeHandle(SQL_HANDLE_DBC, hDbcon);
	}
	if (hEnv)
	{
		SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
	}
}

BOOL OdbcManager::Connect(TCHAR * Constr, TCHAR * UID, TCHAR * PWD)
{
	SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbcon);
	returnVal = SQLConnect(hDbcon, (SQLWCHAR *)Constr, SQL_NTS, (SQLWCHAR *)UID, SQL_NTS,
							(SQLWCHAR *)PWD, SQL_NTS);

	if (returnVal == SQL_SUCCESS || returnVal == SQL_SUCCESS_WITH_INFO)
	{
		returnVal = SQLAllocHandle(SQL_HANDLE_STMT, hDbcon, &hStmt);
		if (returnVal == SQL_SUCCESS || returnVal == SQL_SUCCESS_WITH_INFO)
		{
			returnVal = SQLPrepare(hStmt, (SQLWCHAR*)L"USE dbfinal;", SQL_NTS);
			returnVal = SQLExecute(hStmt);
			if (returnVal == SQL_SUCCESS || returnVal == SQL_SUCCESS_WITH_INFO)
			{
				return true;
			}
			
		}
		else
		{
			hStmt = 0;
			return false;
		}
	}
	else
	{
		return false;
	}
}

//sql 문을 실행하고 성공하면 컬럼의 갯수,데이터가 없으면 -1, 실패 했으면 -2를 반환함
int OdbcManager::Exec(CString szSQL)
{
	SQLSMALLINT ColNum;
	wchar_t* wSql = T2W(szSQL.GetBuffer(0));
	returnVal = SQLExecDirect(hStmt, (SQLWCHAR *)wSql, SQL_NTS);
	if ((returnVal == SQL_SUCCESS) || (returnVal == SQL_SUCCESS_WITH_INFO))
	{
		SQLNumResultCols(hStmt, &ColNum);
		return (int)ColNum;
	}
	else if(returnVal == SQL_NO_DATA)
	{
		return -1;
	}
	else
	{
		return -2;
	}
}

int OdbcManager::BindAndFetchVideoWithPoster(std::vector<CVideoInfo*> *videoInfoVector)
{
	SQLSMALLINT colNum;
	SQLNumResultCols(hStmt, &colNum);
	
	long _idVideo;//SQL_C_LONG 1
	wchar_t _title[257];//SQL_C_WCHAR 2
	wchar_t _fileLoc[513];//SQL_C_WCHAR 3
	int _date;//SQL_C_LONG 4
	wchar_t _director[129];//SQL_C_WCHAR 5
	wchar_t _fileSize[4];//SQL_C_WCHAR 6
	wchar_t _cooperation[129];//SQL_C_WCHAR 7
	//long _idSeries;//SQL_C_LONG 8//나중에 따로 테이블에서 값을 읽어와야함
	long _volume;//SQL_C_LONG 9
	//long _idPoster;//SQL_C_LONG 10//나중에 따로 테이블에서 값을 읽어와야함
	wchar_t _seriesName[257];//SQL_C_WCHAR 12
	long _idSeriesNum;//SQL_C_LONG 13
	wchar_t _imageFileLoc[513];//SQL_C_WCHAR 16

	SQLLEN len_idVideo, len_title, len_fileLoc,
		len_date, len_director, len_fileSize,
		len_cooperation, len_seriesName, len_volume,
		len_idSeriesNum, len_imageFileLoc;

	CString _series;
	CString _PosterLoc;
	CString _actors;
	CString _tags;

	SQLBindCol(hStmt,1, SQL_C_LONG,&_idVideo,0,&len_idVideo);
	SQLBindCol(hStmt, 2, SQL_C_WCHAR, &_title, 257, &len_title);
	SQLBindCol(hStmt, 3, SQL_C_WCHAR, &_fileLoc, 513, &len_fileLoc);
	SQLBindCol(hStmt, 4, SQL_C_LONG, &_date, 0, &len_date);
	SQLBindCol(hStmt, 5, SQL_C_WCHAR, &_director, 129, &len_director);
	SQLBindCol(hStmt, 6, SQL_C_WCHAR, &_fileSize, 4, &len_fileSize);
	SQLBindCol(hStmt, 7, SQL_C_WCHAR, &_cooperation, 129, &len_cooperation);
	SQLBindCol(hStmt, 12, SQL_C_WCHAR, &_seriesName, 257, &len_seriesName);
	SQLBindCol(hStmt, 9, SQL_C_LONG, &_volume, 0, &len_volume);
	SQLBindCol(hStmt, 13, SQL_C_LONG, &_idSeriesNum, 0, &len_idSeriesNum);
	SQLBindCol(hStmt, 16, SQL_C_WCHAR, &_imageFileLoc, 513, &len_imageFileLoc);

	while(true)
	{
		returnVal = SQLFetch(hStmt);
		if (returnVal == SQL_ERROR) 
		{
			return -1;
		}
		if (returnVal == SQL_NO_DATA_FOUND) 
		{
			break;
		}
		if (returnVal == SQL_SUCCESS || returnVal == SQL_SUCCESS_WITH_INFO)
		{
			CVideoInfo* vec = new CVideoInfo();
			vec->idVideo = _idVideo;
			vec->title.Append(_title) ;
			vec->fileLoc = _fileLoc;
			vec->date = _date;
			vec->director = _director;
			vec->fileSize = _fileSize;
			vec->cooperation = _cooperation;
			vec->volume = _volume;
			vec->series.Append(_seriesName);
			CString seriesNum;
			seriesNum.Format(_T("%d"), _idSeriesNum);
			vec->series = vec->series + seriesNum;
			vec->PosterLoc = _imageFileLoc;
			videoInfoVector->push_back(vec);
		}
	}

	std::vector<CVideoInfo*>::iterator iter = videoInfoVector->begin();
	for (; iter != videoInfoVector->end(); ++iter)
	{
		//태그를 얻어오는 부분
		CString sqlTag;
		sqlTag.Format(_T("select t.name from tag as t inner join(select tag_idtag from video_has_tag where video_idvideo = %d) as vt on t.idtag = vt.tag_idtag;"), (*iter)->idVideo);
		Exec(sqlTag);
		wchar_t tag[100];
		SQLLEN len_tag;
		while ((returnVal = SQLFetch(hStmt)) != SQL_NO_DATA_FOUND)
		{
			if (returnVal == SQL_NO_DATA_FOUND)
			{
				break;
			}
			if (returnVal == SQL_SUCCESS || returnVal == SQL_SUCCESS_WITH_INFO)
			{
				SQLGetData(hStmt, 1, SQL_C_WCHAR, &tag, 100, &len_tag);
				(*iter)->tags.Append(tag);
				(*iter)->tags.Append(L" ");
			}
		}
		//배우를 얻어 오는 부분
		CString sqlActor;
		sqlActor.Format(_T("select a.name from Actor as a inner join (select actor_idactor from video_has_actor where video_idvideo = %d) as va on a.idactor = va.actor_idactor;"), (*iter)->idVideo);
		Exec(sqlActor);
		wchar_t actor[100];
		SQLLEN len_actor;
		while ((returnVal = SQLFetch(hStmt)) != SQL_NO_DATA_FOUND)
		{
			if (returnVal == SQL_NO_DATA_FOUND)
			{
				break;
			}
			if (returnVal == SQL_SUCCESS || returnVal == SQL_SUCCESS_WITH_INFO)
			{
				SQLGetData(hStmt, 1, SQL_C_WCHAR, &actor, 100, &len_actor);
				(*iter)->actors.Append(actor);
				(*iter)->actors += " ";
			}
		}

	}

	//저장프로시저 실패
	/*
	std::vector<CVideoInfo*>::iterator iter = videoInfoVector->begin();
	for (; iter != videoInfoVector->end(); ++iter)
	{
		char _actors[1025] = {""};
		char _tags[1025] = { "" };
		SQLLEN len_actors, len_tags;
		returnVal = SQLBindParameter(hStmt, 1, SQL_PARAM_OUTPUT, SQL_C_WCHAR, SQL_LONGVARCHAR, 1024, 0, &_actors, 0, &len_actors);
		CString sp1;
		sp1.Format(_T("{call GetAllActorByVideoId(%d,?)}"), (*iter)->idVideo);
		wchar_t *sp = sp1.GetBuffer();
		returnVal = SQLExecDirect(hStmt, sp, SQL_NTS);
		if (returnVal == SQL_ERROR)
		{
			return -1;
		}
		if (returnVal == SQL_NO_DATA_FOUND)
		{
			break;
		}
		if (returnVal == SQL_SUCCESS || returnVal == SQL_SUCCESS_WITH_INFO)
		{
			int a = 0;
		}

		returnVal = SQLMoreResults(hStmt);
		if (returnVal == SQL_ERROR)
		{
			return -1;
		}
		if (returnVal == SQL_NO_DATA_FOUND)
		{
			break;
		}
		if (returnVal == SQL_SUCCESS || returnVal == SQL_SUCCESS_WITH_INFO)
		{
		}
		(*iter)->actors = _actors;

		returnVal = SQLBindParameter(hStmt, 1, SQL_PARAM_OUTPUT, SQL_C_WCHAR, SQL_C_WCHAR, 0, 0, &_tags, 0, &len_tags);
		CString sp2;
		sp2.Format(_T("{call GetAllTagByVideoId(%d,?)}"), (*iter)->idVideo);
		sp = sp2.GetBuffer();
		returnVal = SQLExecDirect(hStmt, sp, SQL_NTS);
		if (returnVal == SQL_ERROR)
		{
			return -1;
		}
		if (returnVal == SQL_NO_DATA_FOUND)
		{
			break;
		}
		if (returnVal == SQL_SUCCESS || returnVal == SQL_SUCCESS_WITH_INFO)
		{
		}

		returnVal = SQLMoreResults(hStmt);
		if (returnVal == SQL_ERROR)
		{
			return -1;
		}
		if (returnVal == SQL_NO_DATA_FOUND)
		{
			break;
		}
		if (returnVal == SQL_SUCCESS || returnVal == SQL_SUCCESS_WITH_INFO)
		{
		}
		(*iter)->tags = _tags;

	}
	*/
	return 0;
}

