// MovieManagerDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CMovieManagerDlg dialog
class CMovieManagerDlg : public CDialogEx
{
	// Construction
public:
	CMovieManagerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOVIEMANAGER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void MakeVideoInfoGroup();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CComboBox m_combo_category;
	CEdit m_edit_serachKeyword;

	CListCtrl m_listbox_videoList;
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_edit_video_title;
};
