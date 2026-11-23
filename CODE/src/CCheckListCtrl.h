#pragma once
#include <afxcmn.h>

#include"TODOListItem.h"
#include<list>

class CCheckListCtrl :
    public CListCtrl
{
public:
    CCheckListCtrl();
    ///*CCheckListCtrl(std::list<TODOListItem>& list);
    //CCheckListCtrl& operator=(const CCheckListCtrl& other) {
    //    if (&other == this) {
    //        return *this;
    //    }
    //    m_plist = other.m_plist;
    //    return *this;
    //}
    //CCheckListCtrl& operator=(CCheckListCtrl&& other) {
    //    m_plist = std::move(other.m_plist);
    //    return *this;
    //}*/

    virtual ~CCheckListCtrl();

    void ShowItemTip(int item_index, CPoint screenpoint);
    void HideTip();

    void setpList(std::list<TODOListItem>& list) {
        m_plist = &list;
    }

protected:
    void PreSubclassWindow();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT_PTR nIDEvent);

    DECLARE_MESSAGE_MAP()

private:
    std::list<TODOListItem>* m_plist=nullptr;   //对应列表界数据结构的指针
    CToolTipCtrl m_toolTip;
    TOOLINFO m_tipTool{};
    CString m_tipText;

    int m_hoverItem = -1;           //上一个item的行号
    //int m_hoverSubItem = -1;

    bool m_tipVisible = false;
    bool m_trackingLeave = false;

    bool ifTimerRun= false;  //判断计时器是否已经在运作
};

