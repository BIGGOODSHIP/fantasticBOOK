// CDlgTODO.cpp: 实现文件
//
#include "pch.h"
#include "fantasticBOOK.h"
#include "afxdialogex.h"
#include "CDlgTODO.h"
#include "CTipAddTODO.h"
#include "CCheckListCtrl.h"
#include "Data.h"
#include "CTipDelTODO.h"
#include "utility.h"
#include <algorithm>

namespace {
	CString Utf8ToCString(const std::string& text) {
		return CString(CA2T(text.c_str(), CP_UTF8));
	}
}


// CDlgTODO 对话框

IMPLEMENT_DYNAMIC(CDlgTODO, CDialogEx)

CDlgTODO::CDlgTODO(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TODO, pParent)
{
}

CDlgTODO::~CDlgTODO()
{
}

BOOL CDlgTODO::OnInitDialog() {
	CDialogEx::OnInitDialog();
	//初始化列表控件
	m_listTodoCTL.ModifyStyle(
		LVS_TYPEMASK,
		LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS);

	m_listTodoCTL.SetExtendedStyle(
		m_listTodoCTL.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT
		| LVS_EX_GRIDLINES);
	m_listTodoCTL.InsertColumn(0, _T("任务描述"), LVCFMT_LEFT, 120);
	m_listTodoCTL.InsertColumn(1, _T("创建时间"), LVCFMT_LEFT, 120);
	m_listTodoCTL.InsertColumn(2, _T("最晚完成时间"), LVCFMT_LEFT, 120);


	m_listTodoCTL.setpList(m_todoList);
	const bool fileExists = FileExists("TODO.txt");
	m_loadFailed = fileExists && !Load(m_todoList, "TODO.txt");
	for (const auto& item : m_todoList) {
		int index = static_cast<int>(m_listTodoCTL.GetItemCount());
		m_listTodoCTL.InsertItem(
			index,
			Utf8ToCString(item.description));
		m_listTodoCTL.SetItemText(
			index,
			1,
			Utf8ToCString(item.adddate).Right(8));
		m_listTodoCTL.SetItemText(
			index,
			2,
			Utf8ToCString(item.duedate));
	}

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
void CDlgTODO::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TODOLIST, m_listTodoCTL);
}


BEGIN_MESSAGE_MAP(CDlgTODO, CDialogEx)
	ON_BN_CLICKED(IDC_TODO_ADD, &CDlgTODO::OnBnClickedTodoAdd)
	ON_BN_CLICKED(IDC_TODODEL, &CDlgTODO::OnBnClickedTododel)
END_MESSAGE_MAP()


// CDlgTODO 消息处理程序**********************************************

void CDlgTODO::OnBnClickedTodoAdd()
{
	CTipAddTODO addDlg;
	INT_PTR ret = addDlg.DoModal();
	if (ret == IDOK&& addDlg.ifcancel == FALSE) {
		 //获取用户输入的待办事项信息
		TODOListItem newItem;
		newItem.description = addDlg.GetDescription();
		newItem.adddate = addDlg.GetAddDate();
		newItem.duedate = addDlg.GetDueDate();
		newItem.completed = FALSE; // 新添加的任务默认未完成
		//将新任务添加到列表中
		m_todoList.push_back(newItem);
		newItem.description = addDlg.GetShowDescription();
		newItem.adddate = addDlg.GetShowAddDate();
		newItem.duedate = addDlg.GetShowDueDate();
		add(newItem);
	}
	else if(ret==IDCANCEL)
	{
		// 用户取消了操作
		return;
	}
}
// CDlgTODO 消息处理程序**********************************************

//******************************************************************
void CDlgTODO::add(TODOListItem& item) {

	//将新任务添加到列表中
		int index = static_cast<int>(
			m_listTodoCTL.GetItemCount());
	int ret = m_listTodoCTL.InsertItem(index, CString(item.description.c_str())); 
	m_listTodoCTL.SetItemText(index,1, CString(item.adddate.c_str()).Right(8));
	m_listTodoCTL.SetItemText(index,2,CString(item.duedate.c_str()));


}

void CDlgTODO::del(int item_index) {
	// 将新任务添加到内部列表数据结构
	auto it = m_todoList.begin();
	for (int i = 0;i < item_index;i++) {
		++it;
	}
	m_todoList.erase(it);

	//将任务从列表中删去
	m_listTodoCTL.DeleteItem(item_index);


}


void CDlgTODO::OnBnClickedTododel()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = static_cast<int>(
		m_listTodoCTL.GetNextItem(-1, LVNI_SELECTED));
	if (index == -1) {
		return;
	}
	else {
		CTipDelTODO delDlg;
		auto it = m_todoList.begin();
		for (int i = 0;i < index;i++) {
			it++;
		}
		TODOListItem temp = *it;
		CString tiptext = CString(temp.description.c_str());
		delDlg.tipText = tiptext;
		INT_PTR ret=delDlg.DoModal();
		if (ret == IDOK && delDlg.ifcancel == FALSE) {
			//确认删除的操作
			del(index);
			return;
		}
		else if (ret == IDCANCEL)
		{
			// 用户取消了操作
			return;
		}
	}
}
