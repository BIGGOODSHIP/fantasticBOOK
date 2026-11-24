#pragma once
#include "afxdialogex.h"


// CDlgPet 对话框

class CDlgPet : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPet)

public:
	CDlgPet(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgPet();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PET };
#endif

protected:
	BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CFont m_uiFont;
};
