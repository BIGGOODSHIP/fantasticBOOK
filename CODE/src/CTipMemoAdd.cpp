// CTipMemoAdd.cpp: 实现文件
//

#include "pch.h"
#include "fantasticBOOK.h"
#include "afxdialogex.h"
#include "CTipMemoAdd.h"


// CTipMemoAdd 对话框

IMPLEMENT_DYNAMIC(CTipMemoAdd, CDialogEx)

CTipMemoAdd::CTipMemoAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MEMOADD_TIP, pParent)
{

}

CTipMemoAdd::~CTipMemoAdd()
{
}

BOOL CTipMemoAdd::OnInitDialog() {
	CDialogEx::OnInitDialog();
	COLORREF captionColor = RGB(40, 80, 120);
	HRESULT hr = DwmSetWindowAttribute(
		GetSafeHwnd(),
		DWMWA_CAPTION_COLOR,
		&captionColor,
		sizeof(captionColor));

	m_memotextedit.SetLimitText(40);
	
	return TRUE;
}
void CTipMemoAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_MEMOADD_EDIT,memotext);
	DDX_Control(pDX, IDC_MEMOADD_EDIT, m_memotextedit);

}


BEGIN_MESSAGE_MAP(CTipMemoAdd, CDialogEx)
	ON_BN_CLICKED(IDC_MEMOADD_OK, &CTipMemoAdd::OnBnClickedMemoaddOk)
END_MESSAGE_MAP()


// CTipMemoAdd 消息处理程序

void CTipMemoAdd::OnBnClickedMemoaddOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);	//控件到成员变量
	OnOK();
}
