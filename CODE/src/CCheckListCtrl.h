#pragma once
#include <afxcmn.h>

#include"Data.h"
#include<list>
#include<functional>

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

    void setTipTextProvider(std::function<CString(int)> provider) {
        m_tipTextProvider = provider;
    }

    int GetIndex() const {
        return m_index;
    }

    void SetIndex(int item_index) {
        m_index = item_index >= 0 && item_index < GetItemCount()
            ? item_index
            : -1;
    }

protected:
    void PreSubclassWindow();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT_PTR nIDEvent);

    DECLARE_MESSAGE_MAP()

private:
    std::list<TODOListItem>* m_plist=nullptr;   //对应列表界数据结构的指针
    std::function<CString(int)> m_tipTextProvider;
    CToolTipCtrl m_toolTip;
    TOOLINFO m_tipTool{};
    CString m_tipText;

    int m_hoverItem = -1;           //上一个item的行号
    //int m_hoverSubItem = -1;
    int m_index = -1;               //当前双击选中的item索引

    bool m_tipVisible = false;
    bool m_trackingLeave = false;

    bool ifTimerRun= false;  //判断计时器是否已经在运作
};

