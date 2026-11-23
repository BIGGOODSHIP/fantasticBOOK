// CDlgDiary.cpp: 实现文件
//

#include "pch.h"
#include "fantasticBOOK.h"
#include "afxdialogex.h"
#include "CDlgDiary.h"


// CDlgDiary 对话框

IMPLEMENT_DYNAMIC(CDlgDiary, CDialogEx)

CDlgDiary::CDlgDiary(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DIARY, pParent)
{

}

CDlgDiary::~CDlgDiary()
{
}

void CDlgDiary::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDiary, CDialogEx)
END_MESSAGE_MAP()


// CDlgDiary 消息处理程序
