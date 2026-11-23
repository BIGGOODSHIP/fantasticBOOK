#pragma once
#include "afxdialogex.h"


// CTipMemoAdd 对话框

class CTipMemoAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CTipMemoAdd)

public:
	CTipMemoAdd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTipMemoAdd();
	BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEMOADD_TIP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMemoaddOk();
	CString memotext;
	CEdit	m_memotextedit;
};
