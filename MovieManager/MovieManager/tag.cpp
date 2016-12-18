// tag.h : Implementation of the Ctag class



// Ctag implementation

// code generated on 2016년 12월 17일 토요일, 오후 3:11

#include "stdafx.h"
#include "tag.h"
IMPLEMENT_DYNAMIC(Ctag, CRecordset)

Ctag::Ctag(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_idtag = 0;
	m_name = L"";
	m_nFields = 2;
	m_nDefaultType = snapshot;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString Ctag::GetDefaultConnect()
{
	return _T("DSN=dbFinal;DESCRIPTION=FinalProj;SERVER=localhost;UID=root;PWD=next1234;DATABASE=dbfinal;PORT=3306");
}

CString Ctag::GetDefaultSQL()
{
	return _T("[tag]");
}

void Ctag::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[idtag]"), m_idtag);
	RFX_Text(pFX, _T("[name]"), m_name);

}
/////////////////////////////////////////////////////////////////////////////
// Ctag diagnostics

#ifdef _DEBUG
void Ctag::AssertValid() const
{
	CRecordset::AssertValid();
}

void Ctag::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


