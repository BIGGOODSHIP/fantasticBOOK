// CDlgMemo.cpp: 实现文件
//

#include "pch.h"
#include "fantasticBOOK.h"
#include "afxdialogex.h"
#include "CDlgMemo.h"
#include "CTipMemoAdd.h"
#include "CTipMemoClear.h"


// CDlgMemo 对话框

IMPLEMENT_DYNAMIC(CDlgMemo, CDialogEx)

CDlgMemo::CDlgMemo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MEMO, pParent)
{

}

CDlgMemo::~CDlgMemo()
{
}

void CDlgMemo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MEMO_LIST, m_memolist);
}


BEGIN_MESSAGE_MAP(CDlgMemo, CDialogEx)
	ON_BN_CLICKED(IDC_MEMO_ADD, &CDlgMemo::OnBnClickedMemoAdd)
	ON_BN_CLICKED(IDC_MEMO_DEL, &CDlgMemo::OnBnClickedMemoDel)
	ON_BN_CLICKED(IDC_MEMO_CLEAR, &CDlgMemo::OnBnClickedMemoClear)
END_MESSAGE_MAP()


// CDlgMemo 消息处理程序

void CDlgMemo::OnBnClickedMemoAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CTipMemoAdd addDlg;
	int nret=addDlg.DoModal();
	if (nret == IDCANCEL) {
		return;
	}
	
	CString memoText= addDlg.memotext; 
	std::string str = CT2A(memoText.GetString(), CP_UTF8);
	m_memoVec.push_back(str);
	m_memolist.AddString(memoText);
}

void CDlgMemo::OnBnClickedMemoDel()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_memolist.GetCurSel();
	if (index != LB_ERR) {
		auto it = m_memoVec.begin();
		for (int i = 0;i < index;i++) {
			++it;
		}
		m_memoVec.erase(it);
		m_memolist.DeleteString(index);
	}
	else {
		return;
	}
}

void CDlgMemo::OnBnClickedMemoClear()
{
	// TODO: 在此添加控件通知处理程序代码
	CTipMemoClear clearDlg;
	int nret = clearDlg.DoModal();
	if (nret == IDOK && clearDlg.ifcancel == FALSE) {
		//清空的操作
		m_memoVec.clear();
		m_memolist.ResetContent();
		return;
	}
	else if (nret == IDCANCEL)
	{
		// 用户取消了操作
		return;
	}
}

std::vector<std::string>& CDlgMemo::GetVec() {
	return m_memoVec;
}