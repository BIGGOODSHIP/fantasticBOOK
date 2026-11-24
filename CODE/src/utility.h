#pragma once
#include "pch.h"
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<utility>
#include"Writer.h"
#include"Data.h"
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

inline std::string EscapeDiaryContent(const std::string& content)
{
    std::string escaped;
    escaped.reserve(content.size());
    for (const char character : content)
    {
        switch (character)
        {
        case '\\':
            escaped += "\\\\";
            break;
        case '\t':
            escaped += "\\t";
            break;
        case '\r':
            escaped += "\\r";
            break;
        case '\n':
            escaped += "\\n";
            break;
        default:
            escaped += character;
            break;
        }
    }
    return escaped;
}

inline std::string UnescapeDiaryContent(const std::string& content)
{
    std::string unescaped;
    unescaped.reserve(content.size());
    for (size_t i = 0; i < content.size(); ++i)
    {
        if (content[i] != '\\' || i + 1 >= content.size())
        {
            unescaped += content[i];
            continue;
        }

        const char next = content[++i];
        switch (next)
        {
        case '\\':
            unescaped += '\\';
            break;
        case 't':
            unescaped += '\t';
            break;
        case 'r':
            unescaped += '\r';
            break;
        case 'n':
            unescaped += '\n';
            break;
        default:
            unescaped += '\\';
            unescaped += next;
            break;
        }
    }
    return unescaped;
}

inline std::string ToLine(const Diary& node, const std::string& adddate)
{
    std::ostringstream line;
    line << node.index << '\t'
        << adddate << '\t'
        << "@e1:" << EscapeDiaryContent(node.content);
    return line.str();
}

template<class Collection, class WriterType>
void Save(const Collection& collection, WriterType& writer)
{
    int ret=writer.open_for_write();
    if (ret == -1) {
        std::cout << "open for write failur\n";
        return;
    }
    for (const auto& item : collection)
    {
        writer.writetofile(ToLine(item));
    }
}

template<class WriterType>
void SaveDiarys(
    const std::vector<Diary>& diaries,
    const std::vector<std::string>& adddates,
    WriterType& writer)
{
    const size_t count = diaries.size() < adddates.size()
        ? diaries.size()
        : adddates.size();
    for (size_t i = 0; i < count; ++i)
    {
        writer.writetofile(ToLine(diaries[i], adddates[i]));
    }
}

inline bool FromLine(const std::string& text, std::string& memo)
{
    if (text.empty())
    {
        return false;
    }

    memo = text;
    return true;
}

inline bool FromLine(const std::string& line, TODOListItem& node)
{
    const size_t firstTab = line.find('\t');
    if (firstTab == std::string::npos)
    {
        return false;
    }

    const size_t secondTab = line.find('\t', firstTab + 1);
    if (secondTab == std::string::npos)
    {
        return false;
    }

    node.description = line.substr(0, firstTab);
    node.adddate = line.substr(firstTab + 1, secondTab - firstTab - 1);
    node.duedate = line.substr(secondTab + 1);
    node.completed = FALSE;
    return !node.description.empty();
}

inline bool FromLine(
    const std::string& line,
    Diary& node,
    std::string& adddate)
{
    const size_t firstTab = line.find('\t');
    if (firstTab == std::string::npos)
    {
        return false;
    }

    node.index = line.substr(0, firstTab);
    const size_t secondTab = line.find('\t', firstTab + 1);
    if (secondTab == std::string::npos)
    {
        adddate = line.substr(firstTab + 1);
        node.content.clear();
    }
    else
    {
        adddate = line.substr(
            firstTab + 1,
            secondTab - firstTab - 1);
        const std::string content = line.substr(secondTab + 1);
        const std::string prefix = "@e1:";
        if (content.compare(0, prefix.size(), prefix) == 0)
        {
            node.content = UnescapeDiaryContent(
                content.substr(prefix.size()));
        }
        else
        {
            node.content = content;
        }
    }
    return !node.index.empty();
}


template<class Collection>
bool Load(Collection& collection, const std::string& path)
{
    collection.clear();

    std::ifstream input(path);
    if (!input.is_open())
    {
        return false;
    }

    using ValueType = typename Collection::value_type;
    std::string line;
    while (std::getline(input, line))
    {
        ValueType item{};
        if (FromLine(line, item))
        {
            collection.push_back(std::move(item));
        }
    }
    return true;
}

inline bool LoadDiarys(
    std::vector<Diary>& diaries,
    std::vector<std::string>& adddates,
    const std::string& path)
{
    diaries.clear();
    adddates.clear();

    std::ifstream input(path);
    if (!input.is_open())
    {
        return false;
    }

    std::string line;
    while (std::getline(input, line))
    {
        Diary diary;
        std::string adddate;
        if (FromLine(line, diary, adddate))
        {
            diaries.push_back(std::move(diary));
            adddates.push_back(std::move(adddate));
        }
    }
    return true;
}
