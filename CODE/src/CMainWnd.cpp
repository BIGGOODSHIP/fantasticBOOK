// CMainWnd.cpp: 实现文件
//

#include "pch.h"
#include "fantasticBOOK.h"
#include "afxdialogex.h"
#include "CMainWnd.h"
#include"utility.h"

#pragma comment(lib, "dwmapi.lib")


// CMainWnd 对话框

IMPLEMENT_DYNAMIC(CMainWnd, CDialogEx)

CMainWnd::CMainWnd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAINWND, pParent)
{

}

CMainWnd::~CMainWnd()
{
}

BOOL CMainWnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ApplyApplicationIcons(*this);


	COLORREF captionColor = RGB(40, 80, 120);

	HRESULT hr = DwmSetWindowAttribute(
		GetSafeHwnd(),
		DWMWA_CAPTION_COLOR,
		&captionColor,
		sizeof(captionColor));

	// 在这里创建和显示子对话框
	m_dlgMemo.Create(IDD_DIALOG_MEMO, this);
	m_dlgDiary.Create(IDD_DIALOG_DIARY, this);
	m_dlgTODO.Create(IDD_DIALOG_TODO, this);
	m_dlgPet.Create(IDD_DIALOG_PET, this);
	//
	m_pCurrentDlg = &m_dlgMemo; // 默认显示备忘录对话框
	ShowCurrentPage();

	

	return TRUE;
}

void CMainWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainWnd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_MEMO, &CMainWnd::OnBnClickedButtonMemo)
	ON_BN_CLICKED(IDC_BUTTON_TODO, &CMainWnd::OnBnClickedButtonTodo)
	ON_BN_CLICKED(IDC_BUTTON_DIARY, &CMainWnd::OnBnClickedButtonDiary)
	ON_BN_CLICKED(IDC_BUTTON_PET, &CMainWnd::OnBnClickedButtonPet)
END_MESSAGE_MAP()

//////////////////////////////封装工具函数

void CMainWnd::HideAllPages() {
	m_dlgMemo.ShowWindow(SW_HIDE);
	m_dlgDiary.ShowWindow(SW_HIDE);
	m_dlgTODO.ShowWindow(SW_HIDE);
	m_dlgPet.ShowWindow(SW_HIDE);
}
void CMainWnd::ShowCurrentPage() {
	HideAllPages();
	CWnd* host = GetDlgItem(IDC_PAGE_HOST);
	if (host != nullptr) {
		CRect rect;
		host->GetWindowRect(&rect);
		ScreenToClient(&rect);
		m_pCurrentDlg->MoveWindow(&rect);
		m_pCurrentDlg->ShowWindow(SW_SHOWNA);
	}

}





/***************************************************************/
// CMainWnd 消息处理程序

void CMainWnd::OnBnClickedButtonMemo()
{
	m_pCurrentDlg = &m_dlgMemo; // 设置当前显示的子对话框为备忘录
	HideAllPages();
	ShowCurrentPage();
}

void CMainWnd::OnBnClickedButtonTodo()
{
	m_pCurrentDlg = &m_dlgTODO; // 设置当前显示的子对话框为待办事项
	HideAllPages();
	ShowCurrentPage();
}

void CMainWnd::OnBnClickedButtonDiary()
{
	m_pCurrentDlg = &m_dlgDiary; // 设置当前显示的子对话框为日记
	HideAllPages();
	ShowCurrentPage();
}

void CMainWnd::OnBnClickedButtonPet()
{
	m_pCurrentDlg = &m_dlgPet; // 设置当前显示的子对话框为桌面宠物
	HideAllPages();
	ShowCurrentPage();
}
