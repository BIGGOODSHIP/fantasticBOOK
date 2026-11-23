// CDlgTODO.cpp: 实现文件
//
#include "pch.h"
#include "fantasticBOOK.h"
#include "afxdialogex.h"
#include "CDlgTODO.h"
#include "CTipAddTODO.h"
#include "CCheckListCtrl.h"
#include "TODOListItem.h"
#include "CTipDelTODO.h"
#include <algorithm>


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
	int ret = addDlg.DoModal();
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
	int index = m_listTodoCTL.GetItemCount();
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
	int index = m_listTodoCTL.GetNextItem(-1, LVNI_SELECTED);
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
		int ret=delDlg.DoModal();
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
