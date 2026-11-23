#pragma once
#include "afxdialogex.h"


// CTipMemoClear 对话框

class CTipMemoClear : public CDialogEx
{
	DECLARE_DYNAMIC(CTipMemoClear)

public:
	CTipMemoClear(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTipMemoClear();

	BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIPMEMOCLEAR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL ifcancel = FALSE; // 是否取消清空
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
