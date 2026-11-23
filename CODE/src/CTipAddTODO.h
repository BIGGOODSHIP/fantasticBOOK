#pragma once
#include "afxdialogex.h"
#include <string>

// CTipAddTODO 对话框

class CTipAddTODO : public CDialogEx
{
	DECLARE_DYNAMIC(CTipAddTODO)

public:
	CTipAddTODO(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTipAddTODO();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIPADDTODO };
#endif

protected:
	BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CEdit m_editDescription; // 待办事项描述编辑框
	CEdit m_editAddDate;      // 添加日期编辑框
	CEdit m_editDueDate;      // 截止日期编辑框

	std::string m_description; // 待办事项描述
	std::string m_adddate;      // 添加日期
	std::string m_duedate;      // 截止日期

	std::string r_description;
	std::string r_adddate;
	std::string r_duedate;

	//std::string nowdate; // 当前日期  初始显示为当前日期

public:
	BOOL ifcancel = FALSE; // 是否取消添加
	
public:
	std::string GetDescription() const { return r_description; }
	std::string GetAddDate() const { return r_adddate; }
	std::string GetDueDate() const { return r_duedate; }

	std::string GetShowDescription() const { return m_description; }
	std::string GetShowAddDate() const { return m_adddate; }
	std::string GetShowDueDate() const { return m_duedate; }
	afx_msg void OnBnClickedAddtodoCancel();
	afx_msg void OnBnClickedAddtodoAdd();
};
