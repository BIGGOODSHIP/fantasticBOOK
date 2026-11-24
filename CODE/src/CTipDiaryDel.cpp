// CTipDiaryDel.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "CTipDiaryDel.h"
#include "resource.h"
#include <iostream>


// CTipDiaryDel 对话框

IMPLEMENT_DYNAMIC(CTipDiaryDel, CDialogEx)

CTipDiaryDel::CTipDiaryDel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIPDIARYDEL, pParent)
{

}

CTipDiaryDel::~CTipDiaryDel()
{
}

BOOL CTipDiaryDel::OnInitDialog() {
	CDialogEx::OnInitDialog();
	COLORREF captionColor = RGB(40, 80, 120);
	HRESULT hr = DwmSetWindowAttribute(
		GetSafeHwnd(),
		DWMWA_CAPTION_COLOR,
		&captionColor,
		sizeof(captionColor));
	if (index < 0||index>index_max) {
		m_tip.SetWindowText(_T("请选择正确的日记"));
	}
	return TRUE;
}
void CTipDiaryDel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DIARYDEL_TIP,m_tip);
}


BEGIN_MESSAGE_MAP(CTipDiaryDel, CDialogEx)

	ON_BN_CLICKED(IDC_DIRAYDEL_CONFIRM, &CTipDiaryDel::OnBnClickedDiraydelConfirm)
	ON_BN_CLICKED(IDC_DIARYDEL_CANCEL, &CTipDiaryDel::OnBnClickedDiarydelCancel)
END_MESSAGE_MAP()



void CTipDiaryDel::OnBnClickedDiraydelConfirm()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();

}

void CTipDiaryDel::OnBnClickedDiarydelCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ifCancel = TRUE;
	OnOK();
}
