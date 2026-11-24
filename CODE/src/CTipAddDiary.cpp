// CTipAddDiary.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "CTipAddDiary.h"
#include"resource.h"


// CTipAddDiary 对话框

IMPLEMENT_DYNAMIC(CTipAddDiary, CDialogEx)

CTipAddDiary::CTipAddDiary(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIPDIARYADD, pParent)
{

}
BOOL CTipAddDiary::OnInitDialog() {
	CDialogEx::OnInitDialog();
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

	m_edit1.SetLimitText(10);
	CString nowDate;
	nowDate.Format(_T("%04d-%02d-%02d|%02d:%02d:%02d"), year, month, day, hour, minute, second);
	m_edit2.SetWindowText(nowDate);
	return TRUE;
}
CTipAddDiary::~CTipAddDiary()
{
}

void CTipAddDiary::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DIARYADD_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_DIARYADD_EDIT2, m_edit2);
}


BEGIN_MESSAGE_MAP(CTipAddDiary, CDialogEx)
	ON_BN_CLICKED(IDC_TIPDIARYADD_CONFIRM, &CTipAddDiary::OnBnClickedTipdiaryaddConfirm)
	ON_BN_CLICKED(IDC_TIPDIARYADD_CANCEL, &CTipAddDiary::OnBnClickedTipdiaryaddCancel)
END_MESSAGE_MAP()


// CTipAddDiary 消息处理程序

void CTipAddDiary::OnBnClickedTipdiaryaddConfirm()
{
	// TODO: 在此添加控件通知处理程序代码
	CString diary_title;CString diary_context;CString diary_date;
	m_edit1.GetWindowText(diary_title);
	m_edit2.GetWindowText(diary_date);

	if (diary_title == "") {
		return;
	}

	m_diary_title = diary_title;
	m_diary_date = diary_date;
	


	

	OnOK();
}

void CTipAddDiary::OnBnClickedTipdiaryaddCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ifcancel = TRUE;
	OnOK();
}
