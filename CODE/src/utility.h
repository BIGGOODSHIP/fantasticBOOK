#pragma once
#include "pch.h"
#include<string>
#include<iostream>
#include"Writer.h"
#include"TODOListItem.h"
#include<sstream>
#include"resource.h"

inline void ApplyApplicationIcons(CWnd& window)
{
    const HINSTANCE instance = AfxGetInstanceHandle();

    HICON largeIcon = reinterpret_cast<HICON>(
        ::LoadImage(
            instance,
            MAKEINTRESOURCE(IDR_MAINFRAME),
            IMAGE_ICON,
            GetSystemMetrics(SM_CXICON),
            GetSystemMetrics(SM_CYICON),
            LR_DEFAULTCOLOR | LR_SHARED));

    HICON smallIcon = reinterpret_cast<HICON>(
        ::LoadImage(
            instance,
            MAKEINTRESOURCE(IDR_MAINFRAME),
            IMAGE_ICON,
            GetSystemMetrics(SM_CXSMICON),
            GetSystemMetrics(SM_CYSMICON),
            LR_DEFAULTCOLOR | LR_SHARED));

    if (largeIcon != nullptr) {
        window.SetIcon(largeIcon, TRUE);
    }

    if (smallIcon != nullptr) {
        window.SetIcon(smallIcon, FALSE);
    }
}

inline std::string ToLine(const std::string& text)
{
    return text;
}

inline std::string ToLine(const TODOListItem& node)
{
    std::ostringstream line;
    line << node.description<< '\t'
        << node.adddate << '\t'
        << node.duedate;
    return line.str();
}

template<class Collection, class WriterType>
void Save(const Collection& collection, WriterType& writer)
{
    for (const auto& item : collection)
    {
        writer.writetofile(ToLine(item));
    }
}

inline bool FromLine(std::string a_memo,const std::string& text)
{
    a_memo = text;
    return true;
}

inline bool FromLine(const std::string& node)
{
   
}


template<class Collection>
void Load(const Collection& collection,std::string path)
{
    for (const auto& item : collection)
    {
        writer.writetofile(ToLine(item));
    }
}