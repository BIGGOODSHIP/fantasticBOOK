// CTipDelTODO.cpp: 实现文件
//

#include "pch.h"
#include "fantasticBOOK.h"
#include "afxdialogex.h"
#include "CTipDelTODO.h"


// CTipDelTODO 对话框

IMPLEMENT_DYNAMIC(CTipDelTODO, CDialogEx)

CTipDelTODO::CTipDelTODO(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIPDELTODO, pParent)
{

}

CTipDelTODO::~CTipDelTODO()
{
}
BOOL CTipDelTODO::OnInitDialog() {
	CDialogEx::OnInitDialog();

	COLORREF captionColor = RGB(40, 80, 120);
	HRESULT hr = DwmSetWindowAttribute(
		GetSafeHwnd(),
		DWMWA_CAPTION_COLOR,
		&captionColor,
		sizeof(captionColor));

	UpdateData(FALSE);
	return TRUE;
}
void CTipDelTODO::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DELTODOTEXT2, tipText);
}


BEGIN_MESSAGE_MAP(CTipDelTODO, CDialogEx)
	ON_BN_CLICKED(IDC_DELTODO_CANCEL, &CTipDelTODO::OnBnClickedDeltodoCancel)
	ON_BN_CLICKED(IDC_DELTODO_CONFIRM, &CTipDelTODO::OnBnClickedDeltodoConfirm)
END_MESSAGE_MAP()


// CTipDelTODO 消息处理程序

void CTipDelTODO::OnBnClickedDeltodoCancel()
{
	
	// TODO: 在此添加控件通知处理程序代码
	ifcancel = TRUE; // 设置取消标志为 TRUE
	OnOK();
}
void CTipDelTODO::OnBnClickedDeltodoConfirm()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();

}
