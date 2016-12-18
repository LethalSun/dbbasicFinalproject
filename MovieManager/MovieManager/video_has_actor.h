// video_has_actor.h : Declaration of the Cvideo_has_actor

#pragma once

// code generated on 2016년 12월 17일 토요일, 오후 2:50

class Cvideo_has_actor : public CRecordset
{
public:
	Cvideo_has_actor(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Cvideo_has_actor)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_video_idvideo;
	long	m_actor_idactor;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


