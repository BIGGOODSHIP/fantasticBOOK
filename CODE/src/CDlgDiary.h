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
	void SaveToTxt();
	afx_msg void OnBnClickedDiaryadd();
	afx_msg void OnDblclkDiaryindex(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeDiarycontent();
	afx_msg HBRUSH OnCtlColor(
		CDC* pDC,
		CWnd* pWnd,
		UINT nCtlColor);
	CCheckListCtrl m_DiaryIndex;
private:
	CBrush m_diaryEditBrush;			//画刷，设置edit背景色

	void LoadDiarys();
	void LoadDiaryContent(int item_index);
	int AddDiaryItem(const Diary& diary);
	std::vector<Diary> m_diarys;
	std::vector<std::string> m_diaryDates;
public:
	CEdit m_DiaryContent;
};
