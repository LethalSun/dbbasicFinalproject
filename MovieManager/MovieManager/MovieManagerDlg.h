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
	//테스트용 검색결과 만드는 함수
	void MakeVideoInfoGroup();

	//상세 정보를 볼때 각각의 에딧박스에 값을 넣어주는 함수.
	bool InsertIntoVideoInfoListBox();
	
	//영상추가 버튼을 눌렀을때 실행되는함수
	afx_msg void OnBnClickedButton1();
	
	//검색 버튼을 눌렀을때 실행되는 함수
	afx_msg void OnBnClickedButton2();
	
	//검색결과를 간단히 보여주는 아래쪽의 리스트 컨트롤 항목이 클릭 됐을때 실행되는 함수
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	
	//태그 리스트가 더블클릭 되었을 때 실행되는 함수
	afx_msg void OnLbnDblclkList1();
	
	//태그 리스트를 다받아올때 쓰는 MFC전용 클래스
	Ctag m_Db_tag;

	//ODBC와 통신을 담당하는 클래스의 맴버변수
	OdbcManager* m_pOdbcManager;

	//ODbc매니져를 통해서 받아오는 비디오 정보를 담는 벡터 클래스
	std::vector<CVideoInfo*> m_VideoInfo;
	//검색 조건을 선택하는 콤보박스의 변수
	CComboBox m_combo_category;

	//검색 키워드를 입력 받는 에딧박스 변수
	CEdit m_edit_serachKeyword;

	//왼쪽 끝에 있는 태그의 리스트박스
	CListBox m_Listbox_tag;
	
	//검색결과를 간단히 보여주는 아래쪽의 리스트 컨트롤 변수
	CListCtrl m_listbox_videoList;

	//비디오 인포 에딧박스변수들
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

	//비디오 인포 포스터 변수
	CImage* m_poster;

	//인포박스에 선택된 동영상파일의 경로정보.
	CString m_VideoLOC;
	
	afx_msg void OnBnClickedButton5();
};
