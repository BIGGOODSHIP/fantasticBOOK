// CTipMemoClear.cpp: 实现文件
//

#include "pch.h"
#include "fantasticBOOK.h"
#include "afxdialogex.h"
#include "CTipMemoClear.h"


// CTipMemoClear 对话框

IMPLEMENT_DYNAMIC(CTipMemoClear, CDialogEx)

CTipMemoClear::CTipMemoClear(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIPMEMOCLEAR, pParent)
{

}

CTipMemoClear::~CTipMemoClear()
{
	
}
BOOL CTipMemoClear::OnInitDialog() {
	COLORREF captionColor = RGB(40, 80, 120);
	HRESULT hr = DwmSetWindowAttribute(
		GetSafeHwnd(),
		DWMWA_CAPTION_COLOR,
		&captionColor,
		sizeof(captionColor));
	return TRUE;
}
void CTipMemoClear::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTipMemoClear, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTipMemoClear::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTipMemoClear::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTipMemoClear 消息处理程序

void CTipMemoClear::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	OnOK();
}

void CTipMemoClear::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	ifcancel = true;
	OnOK();
}
