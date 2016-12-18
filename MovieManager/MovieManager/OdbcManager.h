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
	SQLHENV hEnv; //ȯ�� �ڵ�
	SQLHDBC hDbcon; //��� ���� �ڵ�
	SQLRETURN returnVal; //���Ŀ� ������ SQL���� �����
	TCHAR col[MAX_COL][255];
	//����
	int FindCol(TCHAR *name);
public:
	SQLHSTMT hStmt; //����ڵ�
	SQLINTEGER lCol[MAX_COL]; //�÷��� ����/���� ����

	OdbcManager();
	~OdbcManager();
	//db�� ����
	BOOL Connect(TCHAR *Constr, TCHAR *UID = NULL, TCHAR *PWD = NULL);
	//sql ���� �����ϰ� �����ϸ� �÷��� ����,�����Ͱ� ������ -1, ���� ������ -2�� ��ȯ��
	int Exec(CString szSQL); //sql ���� �����Ѵ�.
	int BindAndFetchVideoWithPoster(std::vector<CVideoInfo*> *);

	//����
	void Clear(); // Ŀ�� ���� �� �� ���ε�





};