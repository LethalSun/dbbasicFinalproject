// AddVideoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MovieManager.h"
#include "AddVideoDlg.h"
#include "afxdialogex.h"

// AddVideoDlg dialog

IMPLEMENT_DYNAMIC(AddVideoDlg, CDialogEx)

AddVideoDlg::AddVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ADD_VIDEO, pParent)
{
}

AddVideoDlg::~AddVideoDlg()
{
}

void AddVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(AddVideoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &AddVideoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &AddVideoDlg::OnBnClickedButton3)
END_MESSAGE_MAP()

// AddVideoDlg message handlers

void AddVideoDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	printf("[OnBnClickedBtnOpen] \n");
	CStdioFile ftxt;
	CFileException kEx;
	CFileDialog dlg(TRUE, _T("*.csv"), NULL, OFN_FILEMUSTEXIST, _T("CSV Files(*.csv)|*.csv|"), NULL);
	if (dlg.DoModal() == IDOK)
	{
		// Get file name
		CString m_strPath, m_strStatus, m_strFolderPath;

		m_strPath = dlg.GetPathName();
		CString file_name = dlg.GetFileName();
		CString m_strStatus_temp;

		m_strStatus += "File name: ";
		m_strStatus += file_name;
		m_strStatus += "\r\n";

		// Set path to load
		m_strStatus += "File path: ";
		m_strStatus += m_strPath;
		m_strStatus += "\r\n";

		// Save folder path for further saving
		m_strFolderPath = m_strPath.Left(m_strPath.GetLength() - file_name.GetLength());
		m_strStatus += "Folder path: ";
		m_strStatus += m_strFolderPath;
		m_strStatus += "\r\n";

		// Update text
		UpdateData(FALSE);
	}
}

void AddVideoDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	printf("[OnBnClickedBtnOpen] \n");
	CStdioFile ftxt;
	CFileException kEx;
	CFileDialog dlg(TRUE, _T("*.csv"), NULL, OFN_FILEMUSTEXIST, _T("CSV Files(*.csv)|*.csv|"), NULL);
	if (dlg.DoModal() == IDOK)
	{
		// Get file name
		CString m_strPath, m_strStatus, m_strFolderPath;

		m_strPath = dlg.GetPathName();
		CString file_name = dlg.GetFileName();
		CString m_strStatus_temp;

		m_strStatus += "File name: ";
		m_strStatus += file_name;
		m_strStatus += "\r\n";

		// Set path to load
		m_strStatus += "File path: ";
		m_strStatus += m_strPath;
		m_strStatus += "\r\n";

		// Save folder path for further saving
		m_strFolderPath = m_strPath.Left(m_strPath.GetLength() - file_name.GetLength());
		m_strStatus += "Folder path: ";
		m_strStatus += m_strFolderPath;
		m_strStatus += "\r\n";

		// Update text
		UpdateData(FALSE);
	}
}