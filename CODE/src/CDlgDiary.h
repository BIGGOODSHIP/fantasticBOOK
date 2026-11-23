#pragma once
#include "afxdialogex.h"


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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
