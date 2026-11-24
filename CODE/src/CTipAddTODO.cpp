// CTipAddTODO.cpp: 实现文件
//

#include "pch.h"
#include "fantasticBOOK.h"
#include "afxdialogex.h"
#include "CTipAddTODO.h"
#include "FlatButtonStyle.h"
#include <string>


// CTipAddTODO 对话框

IMPLEMENT_DYNAMIC(CTipAddTODO, CDialogEx)

CTipAddTODO::CTipAddTODO(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIPADDTODO, pParent)
{

}

CTipAddTODO::~CTipAddTODO()
{
}

BOOL CTipAddTODO::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 控件创建完成后统一应用浅灰色按钮样式。
	ApplyFlatButtonStyle(*this);
	// 设置当前日期为添加日期
	COLORREF captionColor = RGB(40, 80, 120);
	HRESULT hr = DwmSetWindowAttribute(
		GetSafeHwnd(),
		DWMWA_CAPTION_COLOR,
		&captionColor,
		sizeof(captionColor));
	CTime currentTime = CTime::GetCurrentTime();
	int year = currentTime.GetYear();
	int month = currentTime.GetMonth();
	int day = currentTime.GetDay();
	int hour = currentTime.GetHour();
	int minute = currentTime.GetMinute();
	int second = currentTime.GetSecond();

	CString nowDate;
	nowDate.Format(_T("%04d-%02d-%02d|%02d:%02d:%02d"), year, month, day, hour, minute, second);
	m_editAddDate.SetWindowText(nowDate);

	//设置字符上限
	m_editDescription.SetLimitText(50);
	m_editDueDate.SetLimitText(20);
	return TRUE;  
	// return TRUE unless you set the focus to a control
}

void CTipAddTODO::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADDTODO_EDIT1, m_editDescription);
	DDX_Control(pDX, IDC_ADDTODO_EDIT2, m_editAddDate);
	DDX_Control(pDX, IDC_ADDTODO_EDIT3, m_editDueDate);
}


BEGIN_MESSAGE_MAP(CTipAddTODO, CDialogEx)
	ON_BN_CLICKED(IDC_ADDTODO_CANCEL, &CTipAddTODO::OnBnClickedAddtodoCancel)
	ON_BN_CLICKED(IDC_ADDTODO_ADD, &CTipAddTODO::OnBnClickedAddtodoAdd)
END_MESSAGE_MAP()


// CTipAddTODO 消息处理程序

void CTipAddTODO::OnBnClickedAddtodoCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ifcancel = TRUE; // 设置取消标志为 TRUE
	OnOK();
}

void CTipAddTODO::OnBnClickedAddtodoAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strDescription, strAddDate, strDueDate;
	m_editDescription.GetWindowText(strDescription);
	m_editAddDate.GetWindowText(strAddDate);
	m_editDueDate.GetWindowText(strDueDate);

	//用于显示在ctrl上的数据
	m_description = CT2CA(strDescription);
	m_adddate = CT2CA(strAddDate);
	m_duedate = CT2CA(strDueDate);

	//要存放进数据结构里的实际数据
	r_description = CT2A(strDescription.GetString(), CP_UTF8);
	r_adddate = CT2A(strAddDate.GetString(), CP_UTF8);
	r_duedate = CT2A(strDueDate.GetString(), CP_UTF8);

	OnOK();
}
