#pragma once
#include "afxdialogex.h"
#include<vector>
#include"Data.h"
#include"CCheckListCtrl.h"

// CDlgDiary 对话框

class CDlgDiary : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDiary)

public:
	CDlgDiary(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgDiary();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DIARY };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	std::vector<Diary>& GetDiarys() {
		return m_diarys;
	}
	bool SaveAllToTxt();				//保存所有日记到txt
	bool HasLoadError() const { return m_loadFailed; }
	afx_msg void OnBnClickedDiaryadd();
	afx_msg void OnDblclkDiaryindex(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeDiarycontent();
	afx_msg HBRUSH OnCtlColor(
		CDC* pDC,
		CWnd* pWnd,
		UINT nCtlColor);
	CCheckListCtrl m_DiaryIndex;
	int content_index = -1;						//实际显示内容的索引
	int double_index = -1;						//双击项
	int index = -1;								//单击项
private:
	CBrush m_diaryEditBrush;			//画刷，设置edit背景色

	bool LoadDiarys();
	void LoadDiaryContent(int item_index);
	bool UpdateCurrentDiaryContent();
	int AddDiaryItem(const Diary& diary);
	std::vector<Diary> m_diarys;
	std::vector<std::string> m_diaryDates;
	bool m_loadFailed = false;
public:
	CEdit m_DiaryContent;
	afx_msg void OnBnClickedAdddiarySave();
	afx_msg void OnBnClickedAdddiaryClear();
	afx_msg void OnBnClickedDiarydel();
};
