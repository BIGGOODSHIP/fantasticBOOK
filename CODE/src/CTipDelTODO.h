#pragma once
#include "afxdialogex.h"


// CTipDelTODO 对话框

class CTipDelTODO : public CDialogEx
{
	DECLARE_DYNAMIC(CTipDelTODO)

public:
	CTipDelTODO(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTipDelTODO();
	BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIPDELTODO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_tiptext;			//存放tip控件
	CString tipText;			//存放选中的TODO内容

	BOOL ifcancel = FALSE; // 是否取消添加
	afx_msg void OnBnClickedDeltodoCancel();
	afx_msg void OnBnClickedDeltodoConfirm();
};
