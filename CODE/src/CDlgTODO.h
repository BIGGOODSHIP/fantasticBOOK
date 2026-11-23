#pragma once
#include "afxdialogex.h"
#include "list"
#include<string>
#include"CCheckListCtrl.h"


// CDlgTODO 对话框

class CDlgTODO : public CDialogEx
{

	DECLARE_DYNAMIC(CDlgTODO)

public:
	CDlgTODO(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgTODO();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TODO };
#endif

protected:
	BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	//对外接口
	CCheckListCtrl* GetListCtrl() { return &m_listTodoCTL; }			// 获取待办事项列表控件的指针
	std::list<TODOListItem> GetTodoList() { return m_todoList; } // 获取待办事项列表

	void add(TODOListItem& item); // 添加待办事项
	void del(int item_index); // 删除待办事项
private:
	CCheckListCtrl m_listTodoCTL;			// 待办事项列表控件
	std::list<TODOListItem> m_todoList; // 待办事项列表数据结构

	
public:
	afx_msg void OnBnClickedTodoAdd();
	afx_msg void OnBnClickedTododel();
};
