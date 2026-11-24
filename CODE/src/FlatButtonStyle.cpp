#include "pch.h"
#include "pch.h"
#include "FlatButtonStyle.h"

#include <commctrl.h>

#include <new>
#include <vector>

#pragma comment(lib, "Comctl32.lib")

namespace
{
// 用于识别“本模块已经安装过”的子类过程，避免重复设置样式。
constexpr UINT_PTR kButtonSubclassId = 0xFB01;

// 每个按钮独立保存悬停状态；按下、禁用和焦点状态仍从按钮本身查询。
struct FlatButtonState
{
    bool hovered = false;
    bool trackingMouse = false;
};

// 根据交互状态选择背景色：禁用、按下、悬停、默认依次判断。
COLORREF GetFlatButtonBackground(
    const bool hovered,
    const bool pressed,
    const bool disabled)
{
    if (disabled)
    {
        return RGB(247, 247, 248);
    }

    if (pressed)
    {
        return RGB(215, 219, 225);
    }

    if (hovered)
    {
        return RGB(235, 237, 240);
    }

    return RGB(244, 245, 247);
}

// 根据交互状态选择边框色，使悬停、按下和键盘焦点都能被区分。
COLORREF GetFlatButtonBorder(
    const bool hovered,
    const bool pressed,
    const bool focused,
    const bool disabled)
{
    if (disabled)
    {
        return RGB(225, 227, 230);
    }

    if (pressed)
    {
        return RGB(155, 164, 174);
    }

    if (focused)
    {
        return RGB(132, 150, 170);
    }

    if (hovered)
    {
        return RGB(182, 190, 199);
    }

    return RGB(209, 213, 218);
}

// 使用按钮当前状态自行绘制完整外观。
// 这里不调用默认按钮绘制，因此不会保留系统主题的立体边框和渐变。
void PaintFlatButton(
    HWND window,
    HDC deviceContext,
    const FlatButtonState& state)
{
    RECT clientRect{};
    GetClientRect(window, &clientRect);

    if (IsRectEmpty(&clientRect))
    {
        return;
    }

    // BM_GETSTATE 返回按下、焦点等原生按钮状态，无需在外部重复维护。
    const UINT buttonState = static_cast<UINT>(
        SendMessageW(window, BM_GETSTATE, 0, 0));

    const bool pressed = (buttonState & BST_PUSHED) != 0;
    const bool disabled = IsWindowEnabled(window) == FALSE;
    const bool focused = GetFocus() == window;

    const COLORREF background = GetFlatButtonBackground(
        state.hovered,
        pressed,
        disabled);

    const COLORREF border = GetFlatButtonBorder(
        state.hovered,
        pressed,
        focused,
        disabled);

    const COLORREF textColor = disabled
        ? RGB(158, 164, 171)
        : RGB(54, 61, 70);

    // 保存并恢复 DC 状态，避免字体、文字颜色等设置泄漏给后续绘制。
    const int savedState = SaveDC(deviceContext);

    SetBkMode(deviceContext, TRANSPARENT);
    SetTextColor(deviceContext, textColor);

    CBrush backgroundBrush(background);
    FillRect(deviceContext, &clientRect, backgroundBrush);

    CBrush borderBrush(border);
    FrameRect(deviceContext, &clientRect, borderBrush);

    HFONT font = reinterpret_cast<HFONT>(
        SendMessageW(window, WM_GETFONT, 0, 0));

    HGDIOBJ previousFont = nullptr;
    if (font != nullptr)
    {
        previousFont = SelectObject(deviceContext, font);
    }

    const int textLength = GetWindowTextLengthW(window);
    std::vector<wchar_t> text(
        static_cast<std::size_t>(textLength) + 1,
        L'\0');

    if (textLength > 0)
    {
        GetWindowTextW(
            window,
            text.data(),
            static_cast<int>(text.size()));
    }

    RECT textRect = clientRect;
    textRect.left += 4;
    textRect.right -= 4;

    if (pressed)
    {
        // 按下时让文字轻微下移，提供无需更换字体或布局的按压反馈。
        OffsetRect(&textRect, 0, 1);
    }

    DrawTextW(
        deviceContext,
        text.data(),
        textLength,
        &textRect,
        DT_CENTER |
        DT_VCENTER |
        DT_SINGLELINE |
        DT_END_ELLIPSIS);

    if (previousFont != nullptr)
    {
        SelectObject(deviceContext, previousFont);
    }

    RestoreDC(deviceContext, savedState);
}

// 按钮窗口的子类过程：接管绘制，并在交互状态变化时请求重绘。
// 未处理的消息仍交给 DefSubclassProc，以保留按钮原有行为。
LRESULT CALLBACK FlatButtonSubclassProc(
    HWND window,
    UINT message,
    WPARAM wParam,
    LPARAM lParam,
    UINT_PTR subclassId,
    DWORD_PTR referenceData)
{
    auto* state = reinterpret_cast<FlatButtonState*>(referenceData);

    switch (message)
    {
    case WM_ERASEBKGND:
        // WM_PAINT 会完整覆盖客户区，跳过擦除可减少闪烁。
        return 1;

    case WM_PAINT:
    {
        // 不调用默认按钮绘制，改为绘制统一的浅灰色外观。
        PAINTSTRUCT paint{};
        HDC deviceContext = BeginPaint(window, &paint);

        if (state != nullptr)
        {
            PaintFlatButton(window, deviceContext, *state);
        }

        EndPaint(window, &paint);
        return 0;
    }

    case WM_MOUSEMOVE:
        if (state != nullptr)
        {
            // 鼠标首次进入按钮时记录悬停状态并重绘。
            if (!state->hovered)
            {
                state->hovered = true;
                InvalidateRect(window, nullptr, FALSE);
            }

            if (!state->trackingMouse)
            {
                // 注册 TME_LEAVE 后，鼠标离开时才会收到 WM_MOUSELEAVE。
                TRACKMOUSEEVENT tracking{};
                tracking.cbSize = sizeof(tracking);
                tracking.dwFlags = TME_LEAVE;
                tracking.hwndTrack = window;

                if (TrackMouseEvent(&tracking) != FALSE)
                {
                    state->trackingMouse = true;
                }
            }
        }
        break;

    case WM_MOUSELEAVE:
        // 鼠标离开后恢复普通背景；trackingMouse 同时复位以便下次重新注册。
        if (state != nullptr && state->hovered)
        {
            state->hovered = false;
            state->trackingMouse = false;
            InvalidateRect(window, nullptr, FALSE);
        }
        break;

    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_CAPTURECHANGED:
    case WM_ENABLE:
    case WM_SETFOCUS:
    case WM_KILLFOCUS:
    case WM_SETTEXT:
    case WM_UPDATEUISTATE:
    {
        // 先让按钮处理状态变化，再重绘以显示最新的按下、焦点或禁用外观。
        const LRESULT result = DefSubclassProc(
            window,
            message,
            wParam,
            lParam);

        InvalidateRect(window, nullptr, FALSE);
        return result;
    }

    case WM_KEYDOWN:
    case WM_KEYUP:
    {
        // 空格等键盘操作也会改变按钮按下状态，需要同步刷新视觉反馈。
        const LRESULT result = DefSubclassProc(
            window,
            message,
            wParam,
            lParam);

        InvalidateRect(window, nullptr, FALSE);
        return result;
    }

    case WM_NCDESTROY:
    {
        // 窗口销毁前移除子类并释放按按钮分配的悬停状态。
        const LRESULT result = DefSubclassProc(
            window,
            message,
            wParam,
            lParam);

        RemoveWindowSubclass(
            window,
            FlatButtonSubclassProc,
            subclassId);

        delete state;
        return result;
    }

    default:
        break;
    }

    return DefSubclassProc(
        window,
        message,
        wParam,
        lParam);
}

// EnumChildWindows 回调：只处理标准 Button 控件中的普通按钮和默认按钮。
// 复选框、单选按钮和分组框保持原样，避免破坏它们的专用绘制。
BOOL CALLBACK ApplyFlatButtonStyleToChild(
    HWND child,
    LPARAM)
{
    wchar_t className[32]{};
    GetClassNameW(
        child,
        className,
        static_cast<int>(_countof(className)));

    if (_wcsicmp(className, L"Button") != 0)
    {
        return TRUE;
    }

    const LONG_PTR style = GetWindowLongPtrW(child, GWL_STYLE);
    const LONG_PTR buttonType = style & BS_TYPEMASK;

    if (buttonType != BS_PUSHBUTTON &&
        buttonType != BS_DEFPUSHBUTTON)
    {
        return TRUE;
    }

    // 防止主窗口和子对话框重复调用时给同一个按钮安装多次子类。
    DWORD_PTR existingState = 0;
    if (GetWindowSubclass(
            child,
            FlatButtonSubclassProc,
            kButtonSubclassId,
            &existingState) != FALSE)
    {
        InvalidateRect(child, nullptr, FALSE);
        return TRUE;
    }

    auto* state = new (std::nothrow) FlatButtonState();
    if (state == nullptr)
    {
        return TRUE;
    }

    if (SetWindowSubclass(
            child,
            FlatButtonSubclassProc,
            kButtonSubclassId,
            reinterpret_cast<DWORD_PTR>(state)) == FALSE)
    {
        delete state;
        return TRUE;
    }

    InvalidateRect(child, nullptr, FALSE);
    return TRUE;
}
}

// 公共入口：递归查找窗口树中的按钮。
// 因此调用方只需对当前对话框执行一次，无需为每个按钮维护成员变量。
void ApplyFlatButtonStyle(CWnd& root)
{
    HWND window = root.GetSafeHwnd();
    if (window == nullptr)
    {
        return;
    }

    EnumChildWindows(
        window,
        ApplyFlatButtonStyleToChild,
        0);
}
