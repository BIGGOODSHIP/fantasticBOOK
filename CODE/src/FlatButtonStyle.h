#pragma once

class CWnd;

// 为指定窗口及其所有子窗口中的普通按钮统一设置浅灰色扁平外观。
//
// 实现只子类化按钮的绘制和鼠标消息，不替换原有 CButton 对象，
// 因此按钮 ID、文本、点击通知和原有事件处理都保持不变。
// 应在窗口及其子控件创建完成之后调用，通常在 OnInitDialog() 中。
void ApplyFlatButtonStyle(CWnd& root);
