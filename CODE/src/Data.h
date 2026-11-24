#pragma once
#include<string>
#include "afxdialogex.h"
struct TODOListItem {
	std::string description; // 待办事项描述
	std::string adddate;      // 添加日期
	std::string duedate;      // 截止日期
	BOOL completed;          // 是否完成

};

struct Diary {
	std::string index;		//日记标题
	std::string content;	//日记内容
};


