// CDlgPet.cpp: 实现文件
//

#include "pch.h"
#include "fantasticBOOK.h"
#include "afxdialogex.h"
#include "CDlgPet.h"
#include"utility.h"


// CDlgPet 对话框

IMPLEMENT_DYNAMIC(CDlgPet, CDialogEx)

CDlgPet::CDlgPet(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PET, pParent)
{

}

CDlgPet::~CDlgPet()
{
}
BOOL CDlgPet::OnInitDialog() {
	CDialogEx::OnInitDialog();
	//设置字体
	if (!UiFont::ApplyFontToChildren(
		*this,
		m_uiFont,
		8,             // 9 磅
		FW_BOLD,        // 粗体
		false,          // 斜体
		false,          // 下划线
		false,          // 删除线
		_T("Microsoft YaHei")))
	{
		TRACE(_T("创建或设置字体失败\n"));
	}
	return TRUE;
	
}
void CDlgPet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPet, CDialogEx)
END_MESSAGE_MAP()


// CDlgPet 消息处理程序
