// CDlgPet.cpp: 实现文件
//

#include "pch.h"
#include "fantasticBOOK.h"
#include "afxdialogex.h"
#include "CDlgPet.h"


// CDlgPet 对话框

IMPLEMENT_DYNAMIC(CDlgPet, CDialogEx)

CDlgPet::CDlgPet(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PET, pParent)
{

}

CDlgPet::~CDlgPet()
{
}

void CDlgPet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPet, CDialogEx)
END_MESSAGE_MAP()


// CDlgPet 消息处理程序
