#pragma once
#include "afxdialogex.h"


// CTipAddDiary 对话框

class CTipAddDiary : public CDialogEx
{
	DECLARE_DYNAMIC(CTipAddDiary)

public:
	CTipAddDiary(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTipAddDiary();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIPDIARYADD };
#endif

protected:
	BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit1;
	CEdit m_edit2;
	CString m_diary_title;
	CString m_diary_date;

public:

	BOOL ifcancel = FALSE; // 是否取消添加
	afx_msg void OnBnClickedTipdiaryaddConfirm();
	afx_msg void OnBnClickedTipdiaryaddCancel();
};
