// video_has_actor.h : Implementation of the Cvideo_has_actor class



// Cvideo_has_actor implementation

// code generated on 2016년 12월 17일 토요일, 오후 2:50

#include "stdafx.h"
#include "video_has_actor.h"
IMPLEMENT_DYNAMIC(Cvideo_has_actor, CRecordset)

Cvideo_has_actor::Cvideo_has_actor(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_video_idvideo = 0;
	m_actor_idactor = 0;
	m_nFields = 2;
	m_nDefaultType = snapshot;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString Cvideo_has_actor::GetDefaultConnect()
{
	return _T("DSN=dbFinal;DESCRIPTION=FinalProj;SERVER=localhost;UID=root;PWD=next1234;DATABASE=dbfinal;PORT=3306");
}

CString Cvideo_has_actor::GetDefaultSQL()
{
	return _T("[video_has_actor]");
}

void Cvideo_has_actor::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[video_idvideo]"), m_video_idvideo);
	RFX_Long(pFX, _T("[actor_idactor]"), m_actor_idactor);

}
/////////////////////////////////////////////////////////////////////////////
// Cvideo_has_actor diagnostics

#ifdef _DEBUG
void Cvideo_has_actor::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cvideo_has_actor::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


