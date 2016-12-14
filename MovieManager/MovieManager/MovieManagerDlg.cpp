// MovieManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MovieManager.h"
#include "MovieManagerDlg.h"
#include "afxdialogex.h"
#include "AddVideoDlg.h"
#include "VideoInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVideoInfo videoInfo[100];
void CMovieManagerDlg::MakeVideoInfoGroup()
{
	int idx;
	CString title, actor, tag;

	for (idx = 0; idx < 100; idx++)
	{
		title.Format(_T("Title[%d]"), idx);
		videoInfo[idx].title = title;
		videoInfo[idx].cooperation = title;
		videoInfo[idx].date = title;
		videoInfo[idx].director = title;
		videoInfo[idx].fileSize = title;

		if (idx % 3 == 0)
		{
			actor.Format(_T("AragakiYui"));
			tag.Format(_T("Action"));
		}
		else if (idx % 3 == 1)
		{
			actor.Format(_T("NagasawaMasami"));
			tag.Format(_T("Love"));
		}

		else
		{
			actor.Format(_T("Hitomi"));
			tag.Format(_T("Horror"));
		}
		videoInfo[idx].actor.push_back(actor);
		videoInfo[idx].actor.push_back(actor);
		videoInfo[idx].tag.push_back(tag);
	}
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMovieManagerDlg dialog

CMovieManagerDlg::CMovieManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MOVIEMANAGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMovieManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo_category);
	DDX_Control(pDX, IDC_EDIT1, m_edit_serachKeyword);
	DDX_Control(pDX, IDC_LIST2, m_listbox_videoList);
	DDX_Control(pDX, IDC_EDIT2, m_edit_video_title);
}

BEGIN_MESSAGE_MAP(CMovieManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMovieManagerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMovieManagerDlg::OnBnClickedButton2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CMovieManagerDlg::OnLvnItemchangedList2)
END_MESSAGE_MAP()

// CMovieManagerDlg message handlers

BOOL CMovieManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// �޺��ڽ� ���� �ʱ�ȭ
	m_combo_category.InsertString(0, _T("����"));
	m_combo_category.InsertString(1, _T("���"));
	m_combo_category.InsertString(2, _T("�ø���"));
	// �޺��ڽ� ó�� ����
	m_combo_category.SetCurSel(0);

	// ����Ʈ �ڽ� �ʱ�ȭ
	// ����Ʈ �ʱ�ȭ
	m_listbox_videoList.DeleteAllItems();
	// ����Ʈ ��Ÿ�� ����
	//LVS_EX_FULLROWSELECT  : �������� ������ �� �� �� ��ü�� ������Ų��.
	//LVS_EX_GRIDLINES      : �� �����ۿ� ��輱�� �׷��ش�.
	//LVS_EX_CHECKBOXES     : �� �����ۿ� Check Box�� ǥ���� �ش�.
	//LVS_EX_HEADERDRAGDROP : �÷� ����� �巡�� �����ν� �÷��� ������ �ٲ� �� �ְ� ���ش�.
	m_listbox_videoList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	// ����Ʈ Ÿ��Ʋ ����
	m_listbox_videoList.InsertColumn(0, _T("����"), LVCFMT_LEFT, 220, -1);
	m_listbox_videoList.InsertColumn(1, _T("���"), LVCFMT_LEFT, 150, -1);
	m_listbox_videoList.InsertColumn(2, _T("�±�"), LVCFMT_LEFT, 150, -1);
	//m_listbox_videoList.InsertColumn(3, _T("����"), LVCFMT_CENTER, 50, -1);
	//m_listbox_videoList.InsertColumn(4, _T("���ۻ�"), LVCFMT_CENTER, 50, -1);
	//m_listbox_videoList.InsertColumn(5, _T("��¥"), LVCFMT_CENTER, 50, -1);
	//m_listbox_videoList.InsertColumn(6, _T("����ũ��"), LVCFMT_CENTER, 50, -1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMovieManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMovieManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMovieManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMovieManagerDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	AddVideoDlg dlg;
	dlg.DoModal();
}

void CMovieManagerDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CString keyword, category, actor, tag;
	int categoryIdx;
	int idx, actotrIdx, tagIdx;

	// Ű���� �ҷ�����
	m_edit_serachKeyword.GetWindowTextW(keyword);
	// ī�װ� �ҷ�����
	categoryIdx = m_combo_category.GetCurSel();
	m_combo_category.GetLBText(categoryIdx, category);

	// ������ ���� ����� *todo : keyword������ �����ͺ��̽����� �ҷ�����
	MakeVideoInfoGroup();

	// ��� ������ �����
	m_listbox_videoList.DeleteAllItems();
	// ��� �÷� �����
	//while (m_listbox_videoList.GetHeaderCtrl()->GetItemCount() > 0)
	//{
		//m_listbox_videoList.DeleteColumn(0);
	//}
	// ����Ʈ ������ ����
	int nListPos;
	//nListPos = m_listbox_videoList.GetItemCount();

	for (idx = 0; idx < 100; idx++)
	{
		// ���� �±� �ʱ�ȭ
		actor = _T("");
		tag = _T("");

		// ����Ʈ ��ȭ ����
		m_listbox_videoList.InsertItem(idx, videoInfo[idx].title);
		// ����Ʈ ���
		for (actotrIdx = 0; actotrIdx < (videoInfo[idx].actor.size()); actotrIdx++)
		{
			actor += videoInfo[idx].actor.at(actotrIdx);
			actor += _T(" ");
		}
		m_listbox_videoList.SetItem(idx, 1, LVIF_TEXT, actor, 0, 0, 0, NULL);
		// ����Ʈ �±�
		for (tagIdx = 0; tagIdx < (videoInfo[idx].actor.size()); tagIdx++)
		{
			tag += videoInfo[idx].actor.at(tagIdx);
			tag += _T(" ");
		}
		m_listbox_videoList.SetItem(idx, 2, LVIF_TEXT, tag, 0, 0, 0, NULL);
	}
	// ListBox ��Ʈ�� �ڵ� ��ũ��
	//m_listbox_videoList.SendMessage(WM_VSCROLL, SB_BOTTOM);
}

void CMovieManagerDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int m_nSelectedItem;
	CString title;

	m_nSelectedItem = pNMLV->iItem;
	title = m_listbox_videoList.GetItemText(m_nSelectedItem, 0);

	m_edit_video_title.SetWindowTextW(title);
	//UpdateData(false);
}