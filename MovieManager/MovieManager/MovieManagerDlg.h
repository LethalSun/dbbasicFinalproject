// MovieManagerDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "tag.h"
#include "OdbcManager.h"
#include <vector>
#include "atlimage.h" 
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
	//�׽�Ʈ�� �˻���� ����� �Լ�
	void MakeVideoInfoGroup();

	//�� ������ ���� ������ �����ڽ��� ���� �־��ִ� �Լ�.
	bool InsertIntoVideoInfoListBox();
	
	//�����߰� ��ư�� �������� ����Ǵ��Լ�
	afx_msg void OnBnClickedButton1();
	
	//�˻� ��ư�� �������� ����Ǵ� �Լ�
	afx_msg void OnBnClickedButton2();
	
	//�˻������ ������ �����ִ� �Ʒ����� ����Ʈ ��Ʈ�� �׸��� Ŭ�� ������ ����Ǵ� �Լ�
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	
	//�±� ����Ʈ�� ����Ŭ�� �Ǿ��� �� ����Ǵ� �Լ�
	afx_msg void OnLbnDblclkList1();
	
	//�±� ����Ʈ�� �ٹ޾ƿö� ���� MFC���� Ŭ����
	Ctag m_Db_tag;

	//ODBC�� ����� ����ϴ� Ŭ������ �ɹ�����
	OdbcManager* m_pOdbcManager;

	//ODbc�Ŵ����� ���ؼ� �޾ƿ��� ���� ������ ��� ���� Ŭ����
	std::vector<CVideoInfo*> m_VideoInfo;
	//�˻� ������ �����ϴ� �޺��ڽ��� ����
	CComboBox m_combo_category;

	//�˻� Ű���带 �Է� �޴� �����ڽ� ����
	CEdit m_edit_serachKeyword;

	//���� ���� �ִ� �±��� ����Ʈ�ڽ�
	CListBox m_Listbox_tag;
	
	//�˻������ ������ �����ִ� �Ʒ����� ����Ʈ ��Ʈ�� ����
	CListCtrl m_listbox_videoList;

	//���� ���� �����ڽ�������
	CEdit m_edit_video_title;
	CEdit m_edit_video_actors;
	CEdit m_edit_video_tags;
	CEdit m_edit_video_series;
	CEdit m_edit_video_volume;
	CEdit m_edit_video_director;
	CEdit m_edit_video_date;
	CEdit m_edit_video_corp;
	CEdit m_edit_video_size;
	CStatic m_picture_poster;

	//���� ���� ������ ����
	CImage* m_poster;

	//�����ڽ��� ���õ� ������������ �������.
	CString m_VideoLOC;
	
	afx_msg void OnBnClickedButton5();
};
