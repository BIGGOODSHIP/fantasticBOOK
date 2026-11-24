#pragma once
#include "afxdialogex.h"


// CTipDiaryDel 对话框

class CTipDiaryDel : public CDialogEx
{
	DECLARE_DYNAMIC(CTipDiaryDel)

public:
	CTipDiaryDel(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTipDiaryDel();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif
public:
	BOOL ifCancel = FALSE;
	int index=0;		//用于判断显示哪种提示串,当前选中项的索引
	int index_max;		//用于保存最大索引数

protected:
	BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	 
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDiraydelConfirm();
	afx_msg void OnBnClickedDiarydelCancel();
private:
	CStatic m_tip;
};
