#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include "sql.h"
#include "sqlext.h"
#include "VideoInfo.h"

class OdbcManager
{
public:
	enum{MAX_COL = 100,
	};

private:
	SQLHENV hEnv; //환경 핸들
	SQLHDBC hDbcon; //디비 연결 핸들
	SQLRETURN returnVal; //최후에 실행한 SQL문의 결과값
	TCHAR col[MAX_COL][255];
	//보류
	int FindCol(TCHAR *name);
public:
	SQLHSTMT hStmt; //명령핸들
	SQLINTEGER lCol[MAX_COL]; //컬럼의 길이/상태 정보

	OdbcManager();
	~OdbcManager();
	//db에 연결
	BOOL Connect(TCHAR *Constr, TCHAR *UID = NULL, TCHAR *PWD = NULL);
	//sql 문을 실행하고 성공하면 컬럼의 갯수,데이터가 없으면 -1, 실패 했으면 -2를 반환함
	int Exec(CString szSQL); //sql 문을 실행한다.
	int BindAndFetchVideoWithPoster(std::vector<CVideoInfo*> *);

	//보류
	void Clear(); // 커서 해제 및 언 바인딩





};