#pragma once

// AddVideoDlg dialog

class AddVideoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddVideoDlg)

public:
	AddVideoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~AddVideoDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_VIDEO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
