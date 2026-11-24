// CDlgDiary.cpp: 实现文件
//

#include "pch.h"
#include "fantasticBOOK.h"
#include "afxdialogex.h"
#include "CDlgDiary.h"
#include "CTipAddDiary.h"
#include "Writer.h"
#include "utility.h"
#include "CTipDiaryDel.h"

namespace {
	CString Utf8ToCString(const std::string& text) {
		return CString(CA2T(text.c_str(), CP_UTF8));
	}

	int CALLBACK CharacterWordBreakProc(
		LPTSTR text,
		int current,
		int count,
		int code) {
		UNREFERENCED_PARAMETER(text);

		if (current < 0) {
			current = 0;
		}
		if (current > count) {
			current = count;
		}

		switch (code) {
		case WB_LEFT:
			return current > 0 ? current - 1 : 0;
		case WB_RIGHT:
			return current < count ? current + 1 : count;
		case WB_ISDELIMITER:
			return TRUE;
		default:
			return current;
		}
	}
}


// CDlgDiary 对话框

IMPLEMENT_DYNAMIC(CDlgDiary, CDialogEx)

CDlgDiary::CDlgDiary(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DIARY, pParent)
{

}

CDlgDiary::~CDlgDiary()
{
}

BOOL CDlgDiary::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_DiaryContent.SendMessage(
		EM_SETWORDBREAKPROC,
		0,
		reinterpret_cast<LPARAM>(CharacterWordBreakProc));

	m_DiaryIndex.ModifyStyle(
		LVS_TYPEMASK,
		LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	m_DiaryIndex.SetExtendedStyle(
		m_DiaryIndex.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT
		| LVS_EX_GRIDLINES);
	m_DiaryIndex.InsertColumn(0, _T("日记"), LVCFMT_LEFT, 150);
	m_DiaryIndex.setTipTextProvider([this](int item_index) {
		if (item_index < 0
			|| item_index >= static_cast<int>(m_diarys.size())
			|| item_index >= static_cast<int>(m_diaryDates.size())) {
			return CString();
		}

		CString createDate = Utf8ToCString(m_diaryDates[item_index]);
		CString diaryName = Utf8ToCString(m_diarys[item_index].index);
		CString tipText;
		tipText.Format(
			_T("创建日期：%s\n日记名：%s"),
			createDate.GetString(),
			diaryName.GetString());
		return tipText;
	});


	//创建画刷
	m_diaryEditBrush.CreateSolidBrush(RGB(247, 242, 234));

	LoadDiarys();
	return TRUE;
}

void CDlgDiary::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DIARYINDEX, m_DiaryIndex);
	DDX_Control(pDX, IDC_DIARYCONTENT, m_DiaryContent);
}


BEGIN_MESSAGE_MAP(CDlgDiary, CDialogEx)
	ON_BN_CLICKED(IDC_DIARYADD, &CDlgDiary::OnBnClickedDiaryadd)
	ON_NOTIFY(NM_DBLCLK, IDC_DIARYINDEX, &CDlgDiary::OnDblclkDiaryindex)
	ON_EN_CHANGE(IDC_DIARYCONTENT, &CDlgDiary::OnEnChangeDiarycontent)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ADDDIARY_SAVE, &CDlgDiary::OnBnClickedAdddiarySave)
	ON_BN_CLICKED(IDC_ADDDIARY_CLEAR, &CDlgDiary::OnBnClickedAdddiaryClear)
	ON_BN_CLICKED(IDC_DIARYDEL, &CDlgDiary::OnBnClickedDiarydel)
END_MESSAGE_MAP()


// CDlgDiary 消息处理程序

void CDlgDiary::OnBnClickedDiaryadd()
{
	// TODO: 在此添加控件通知处理程序代码
	CTipAddDiary addDlg;
	INT_PTR nret = addDlg.DoModal();
	if (nret == IDOK && addDlg.ifcancel == FALSE) {
		//增加日记的操作(显示和添加到数据结构)
		Diary diary;
		diary.index = CT2A(addDlg.m_diary_title.GetString(), CP_UTF8);
		diary.content.clear();
		m_diarys.push_back(diary);
		std::string adddate = CT2A(addDlg.m_diary_date.GetString(), CP_UTF8);
		m_diaryDates.push_back(adddate);
		int item_index = AddDiaryItem(diary);
		m_DiaryIndex.SetItemState(
			item_index,
			LVIS_SELECTED | LVIS_FOCUSED,
			LVIS_SELECTED | LVIS_FOCUSED);
		m_DiaryIndex.SetIndex(item_index);
		m_DiaryContent.SetWindowText(_T(""));

		return;
	}
	else if (nret == IDCANCEL)
	{
		// 用户取消了操作
		return;
	}



}

void CDlgDiary::OnDblclkDiaryindex(NMHDR* pNMHDR, LRESULT* pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	LoadDiaryContent(m_DiaryIndex.GetIndex());
	double_index= m_DiaryIndex.GetIndex();
	content_index = double_index;
	*pResult = 0;
}

void CDlgDiary::OnEnChangeDiarycontent()
{
	UpdateCurrentDiaryContent();
}

void CDlgDiary::LoadDiaryContent(int item_index)
{
	if (item_index < 0
		|| item_index >= static_cast<int>(m_diarys.size())) {
		return;
	}
	/*if (item_index == 0) {
		return;
	}*/

	m_DiaryContent.SetWindowText(
		Utf8ToCString(m_diarys[item_index].content));
}

int CDlgDiary::AddDiaryItem(const Diary& diary)
{
	int item_index = static_cast<int>(m_DiaryIndex.GetItemCount());
	m_DiaryIndex.InsertItem(
		item_index,
		Utf8ToCString(diary.index));
	return item_index;
}

bool CDlgDiary::LoadDiarys()
{
	const bool fileExists = FileExists("Diary.txt");
	const bool loaded =
		::LoadDiarys(m_diarys, m_diaryDates, "Diary.txt");
	m_loadFailed = fileExists && !loaded;

	m_DiaryIndex.SetIndex(-1);
	m_DiaryIndex.DeleteAllItems();
	m_DiaryContent.SetWindowText(_T(""));
	content_index = -1;
	double_index = -1;
	index = -1;
	for (const auto& diary : m_diarys) {
		AddDiaryItem(diary);
	}
	return !m_loadFailed;
}

bool CDlgDiary::UpdateCurrentDiaryContent()
{
	const int item_index = m_DiaryIndex.GetIndex();
	if (item_index < 0
		|| item_index >= static_cast<int>(m_diarys.size())
		|| item_index >= static_cast<int>(m_diaryDates.size())) {
		return false;
	}

	CString content;
	m_DiaryContent.GetWindowText(content);
	m_diarys[item_index].content =
		CT2A(content.GetString(), CP_UTF8);
	content_index = item_index;
	return true;
}

bool CDlgDiary::SaveAllToTxt()
{
	if (m_loadFailed) {
		return false;
	}

	Writer& writer = Writer::GetInstance();
	writer.setpath("Diary.txt");
	return ::SaveDiarys(m_diarys, m_diaryDates, writer);
}

HBRUSH CDlgDiary:: OnCtlColor(
	CDC* pDC,
	CWnd* pWnd,
	UINT nCtlColor) {
	if (pWnd->GetDlgCtrlID() == IDC_DIARYCONTENT)
	{
		// 编辑框背景颜色
		pDC->SetBkColor(RGB(247, 242, 234));

		// 编辑框文字颜色
		pDC->SetTextColor(RGB(45, 22, 45));

		// 返回用于填充背景的画刷
		return m_diaryEditBrush;
	}

	return CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
}
void CDlgDiary::OnBnClickedAdddiarySave()
{
	if (!UpdateCurrentDiaryContent()
		|| !SaveAllToTxt()) {
		AfxMessageBox(_T("日记保存失败，请检查文件是否可写。"));
	}
}

void CDlgDiary::OnBnClickedAdddiaryClear()
{
	m_DiaryContent.SetWindowText(_T(""));
	if (UpdateCurrentDiaryContent()
		&& !SaveAllToTxt()) {
		AfxMessageBox(_T("日记保存失败，请检查文件是否可写。"));
	}
}

void CDlgDiary::OnBnClickedDiarydel()
{
	const int item = static_cast<int>(
		m_DiaryIndex.GetNextItem(-1, LVNI_SELECTED));
	if (item < 0) {
		return;
	}

	index = item;
	CTipDiaryDel delDlg;
	delDlg.index = item;
	delDlg.index_max =
		static_cast<int>(m_DiaryIndex.GetItemCount()) - 1;
	INT_PTR nret=delDlg.DoModal();
	if (item >= static_cast<int>(m_diarys.size())
		|| item >= static_cast<int>(m_diaryDates.size())) {
		return;
	}
	if (nret == IDOK && delDlg.ifCancel == FALSE) {
		//确认删除的操作
		auto it1 = m_diarys.begin();auto it2 = m_diaryDates.begin();
		for (int i = 0;i < item;i++) {
			it1++;
			it2++;
		}
		m_diarys.erase(it1);
		m_diaryDates.erase(it2);
		m_DiaryIndex.DeleteItem(item);
		m_DiaryIndex.SetIndex(-1);
		content_index = -1;
		double_index = -1;
		index = -1;
		m_DiaryContent.SetWindowText(_T(""));
		if (!SaveAllToTxt()) {
			AfxMessageBox(_T("日记删除后保存失败，请检查文件是否可写。"));
		}
	}
	else if (nret == IDCANCEL)
	{
		// 用户取消了操作
		return;
	}
	//...
}
