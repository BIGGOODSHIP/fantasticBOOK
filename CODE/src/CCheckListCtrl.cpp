#include "pch.h"
#include "CCheckListCtrl.h"
#include<list>
#include"TODOListItem.h"

//定时器编号和时间
static const UINT_PTR HOVER_TIMER_ID = 1;
static const UINT HOVER_DELAY_MS = 600;

BEGIN_MESSAGE_MAP(CCheckListCtrl, CListCtrl)
    ON_WM_MOUSEMOVE()
    ON_WM_TIMER()
END_MESSAGE_MAP()

CCheckListCtrl::CCheckListCtrl()
{
}
//CCheckListCtrl::CCheckListCtrl(std::list<TODOListItem>& list) {
//    m_plist = &list;
//}
CCheckListCtrl::~CCheckListCtrl()
{
}

void CCheckListCtrl::PreSubclassWindow() {
    CListCtrl::PreSubclassWindow();

    if (m_toolTip.GetSafeHwnd() != nullptr)
        return;

    if (!m_toolTip.Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX))
        return;
    m_tipTool.cbSize = sizeof(m_tipTool);
    m_tipTool.uFlags = TTF_TRACK | TTF_ABSOLUTE | TTF_IDISHWND;
    m_tipTool.hwnd = GetSafeHwnd();
    m_tipTool.uId = reinterpret_cast<UINT_PTR>(GetSafeHwnd());

    m_tipTool.lpszText = const_cast<LPTSTR>(_T(""));

    m_toolTip.SendMessage(
        TTM_ADDTOOL,
        0,
        reinterpret_cast<LPARAM>(&m_tipTool));
}

void CCheckListCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
    CListCtrl::OnMouseMove(nFlags, point);

    // 这里以后写命中测试和悬停状态判断

    int newItem = HitTest(point);

    if (newItem == m_hoverItem) {
        
        //HideTip();
        if (ifTimerRun) {
            return;
        }
        CPoint screenPoint;
        GetCursorPos(&screenPoint);

        CPoint clientPoint = screenPoint;
        ScreenToClient(&clientPoint);

        int currentItem = HitTest(clientPoint);

        if (currentItem < 0 ||
            currentItem != m_hoverItem)
        {
            m_hoverItem = -1;
            return;
        }

        // 下一步在这里显示 Tooltip
        ShowItemTip(currentItem, screenPoint);
        return;
    }
    m_hoverItem = newItem;
    
    
    HideTip();

    //KillTimer(HOVER_TIMER_ID);

    m_hoverItem = newItem;
    if (m_hoverItem >= 0)
    {
        // 在新 item 上重新等待 2 秒
        SetTimer(
            HOVER_TIMER_ID,
            HOVER_DELAY_MS,
            nullptr);
        ifTimerRun = true;
    }
}

void CCheckListCtrl::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent != HOVER_TIMER_ID)
    {
        CListCtrl::OnTimer(nIDEvent);
        return;
    }

    KillTimer(HOVER_TIMER_ID);

    CPoint screenPoint;
    GetCursorPos(&screenPoint);

    CPoint clientPoint = screenPoint;
    ScreenToClient(&clientPoint);

    int currentItem = HitTest(clientPoint);

    if (currentItem < 0 ||
        currentItem != m_hoverItem)
    {
        m_hoverItem = -1;
        return;
    }

    // 下一步在这里显示 Tooltip
    ShowItemTip(currentItem, screenPoint);
    ifTimerRun = false;
    KillTimer(HOVER_TIMER_ID);

}

//显示itemtip的函数封装
void CCheckListCtrl::ShowItemTip(int item_index, CPoint screenpoint) {
    CString description = GetItemText(item_index, 0);
    auto it = m_plist->begin();
    for (int i = 0;i < item_index;++i) {
        ++it;
    }
    CString addDate = CString((*it).adddate.c_str());
    CString dueDate = GetItemText(item_index, 2);

    m_tipText.Format(
        _T("任务描述: %s    创建时间：%s    最晚完成时间：%s"),
        description.GetString(),
        addDate.GetString(),
        dueDate.GetString());
    m_tipTool.lpszText =
        const_cast<LPTSTR>(
            static_cast<LPCTSTR>(m_tipText));
    m_toolTip.SendMessage(
        TTM_UPDATETIPTEXT,
        0,
        reinterpret_cast<LPARAM>(&m_tipTool));
    CPoint tipPoint = screenpoint;
    tipPoint.Offset(18, 18);

    m_toolTip.SendMessage(
        TTM_TRACKPOSITION,
        0,
        MAKELPARAM(tipPoint.x, tipPoint.y));
    if (!m_tipVisible)
    {
        m_toolTip.SendMessage(
            TTM_TRACKACTIVATE,
            TRUE,
            reinterpret_cast<LPARAM>(&m_tipTool));

        m_tipVisible = true;
    }
}

void CCheckListCtrl::HideTip() {
    KillTimer(HOVER_TIMER_ID);

    if (m_tipVisible &&
        m_toolTip.GetSafeHwnd() != nullptr)
    {
        m_toolTip.SendMessage(
            TTM_TRACKACTIVATE,
            FALSE,
            reinterpret_cast<LPARAM>(&m_tipTool));

        m_tipVisible = false;
    }
}