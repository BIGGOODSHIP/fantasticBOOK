#pragma once
#include "afxdialogex.h"
#include<vector>
#include<string>


// CDlgMemo 对话框

class CDlgMemo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMemo)

public:
	CDlgMemo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgMemo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MEMO };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMemoAdd();
	afx_msg void OnBnClickedMemoDel();
	afx_msg void OnBnClickedMemoClear();

	std::vector<std::string>& GetVec();
	bool HasLoadError() const { return m_loadFailed; }
private:
	std::vector<std::string>	m_memoVec;	//存储备忘条目的数据结构
	CListBox m_memolist;					//list控件
	bool m_loadFailed = false;
};
