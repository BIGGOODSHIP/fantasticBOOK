#pragma once
#include "afxdialogex.h"
#include"flatButtonStyle.h"
#include "CDlgMemo.h"
#include "CDlgDiary.h"
#include "CDlgTODO.h"
#include "CDlgPet.h"


// CMainWnd 对话框

class CMainWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CMainWnd)

public:
	CMainWnd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMainWnd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINWND };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CDlgMemo m_dlgMemo; // 备忘录对话框对象
	CDlgDiary m_dlgDiary; // 日记对话框对象
	CDlgTODO m_dlgTODO; // 待办事项对话框对象
	CDlgPet m_dlgPet; // 宠物对话框对象

	CWnd* m_pCurrentDlg; // 当前显示的子对话框指针

public:
	CDlgMemo* GetDlgMemo() { return &m_dlgMemo; } // 获取备忘录对话框对象的指针
	CDlgDiary* GetDlgDiary() { return &m_dlgDiary; } // 获取日记对话框对象的指针
	CDlgTODO* GetDlgTODO() { return &m_dlgTODO; } // 获取待办事项对话框对象的指针
	CDlgPet* GetDlgPet() { return &m_dlgPet; } // 获取宠物对话框对象的指针

	void ShowCurrentPage(); // 显示当前子对话框
	void HideAllPages();//隐藏所有子对话框
public:
	//message functions
	afx_msg void OnBnClickedButtonMemo();
	afx_msg void OnBnClickedButtonTodo();
	afx_msg void OnBnClickedButtonDiary();
	afx_msg void OnBnClickedButtonPet();
};
