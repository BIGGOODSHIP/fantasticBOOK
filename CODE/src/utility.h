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

inline bool FileExists(const std::string& path)
{
    const DWORD attributes = GetFileAttributesA(path.c_str());
    if (attributes != INVALID_FILE_ATTRIBUTES)
    {
        return true;
    }

    const DWORD error = GetLastError();
    return error != ERROR_FILE_NOT_FOUND
        && error != ERROR_PATH_NOT_FOUND;
}

inline std::string EscapeField(const std::string& content);
inline std::string UnescapeField(const std::string& content);

inline std::string ToLine(const std::string& text)
{
    return "@m1:" + EscapeField(text);
}

inline std::string ToLine(const TODOListItem& node)
{
    std::ostringstream line;
    line << "@t2:"
        << EscapeField(node.description) << '\t'
        << EscapeField(node.adddate) << '\t'
        << EscapeField(node.duedate) << '\t'
        << (node.completed ? 1 : 0);
    return line.str();
}

inline std::string EscapeField(const std::string& content)
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

inline std::string UnescapeField(const std::string& content)
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
        << "@e1:" << EscapeField(node.content);
    return line.str();
}

template<class Collection, class WriterType>
bool Save(const Collection& collection, WriterType& writer)
{
    if (!writer.open_for_write()) {
        return false;
    }

    for (const auto& item : collection)
    {
        if (!writer.writetofile(ToLine(item))) {
            return false;
        }
    }
    return writer.commit();
}

template<class WriterType>
bool SaveDiarys(
    const std::vector<Diary>& diaries,
    const std::vector<std::string>& adddates,
    WriterType& writer)
{
    if (diaries.size() != adddates.size()) {
        return false;
    }

    if (!writer.open_for_write()) {
        return false;
    }

    for (size_t i = 0; i < diaries.size(); ++i)
    {
        if (!writer.writetofile(ToLine(diaries[i], adddates[i]))) {
            return false;
        }
    }
    return writer.commit();
}

inline bool FromLine(const std::string& text, std::string& memo)
{
    if (text.empty())
    {
        return false;
    }

    const std::string prefix = "@m1:";
    if (text.compare(0, prefix.size(), prefix) == 0)
    {
        memo = UnescapeField(text.substr(prefix.size()));
    }
    else
    {
        memo = text;
    }
    return true;
}

inline bool FromLine(const std::string& line, TODOListItem& node)
{
    const std::string prefix = "@t2:";
    const bool versioned =
        line.compare(0, prefix.size(), prefix) == 0;
    const std::string content =
        versioned ? line.substr(prefix.size()) : line;

    const size_t firstTab = content.find('\t');
    if (firstTab == std::string::npos)
    {
        return false;
    }

    const size_t secondTab = content.find('\t', firstTab + 1);
    if (secondTab == std::string::npos)
    {
        return false;
    }

    if (versioned)
    {
        const size_t thirdTab = content.find('\t', secondTab + 1);
        if (thirdTab == std::string::npos)
        {
            return false;
        }

        node.description = UnescapeField(
            content.substr(0, firstTab));
        node.adddate = UnescapeField(
            content.substr(firstTab + 1, secondTab - firstTab - 1));
        node.duedate = UnescapeField(
            content.substr(secondTab + 1, thirdTab - secondTab - 1));
        node.completed =
            content.substr(thirdTab + 1) == "1" ? TRUE : FALSE;
    }
    else
    {
        node.description = content.substr(0, firstTab);
        node.adddate = content.substr(
            firstTab + 1,
            secondTab - firstTab - 1);
        node.duedate = content.substr(secondTab + 1);
        node.completed = FALSE;
    }
    return true;
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
            node.content = UnescapeField(
                content.substr(prefix.size()));
        }
        else
        {
            node.content = content;
        }
    }
    return true;
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
        if (line.empty())
        {
            continue;
        }

        ValueType item{};
        if (!FromLine(line, item))
        {
            collection.clear();
            return false;
        }
        collection.push_back(std::move(item));
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
        if (line.empty())
        {
            continue;
        }

        Diary diary;
        std::string adddate;
        if (!FromLine(line, diary, adddate))
        {
            diaries.clear();
            adddates.clear();
            return false;
        }
        diaries.push_back(std::move(diary));
        adddates.push_back(std::move(adddate));
    }
    return true;
}
