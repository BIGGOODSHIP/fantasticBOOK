#pragma once
#include<iostream>
#include<fstream>
//对外输出工具类
//往外写内容到指定文件
class Writer
{
private:
	Writer() {};
public:

	~Writer() {};

	Writer(const Writer& other) = delete;
	Writer(Writer&& other) = delete;
	Writer& operator=(const Writer& other) = delete;
	Writer& operator=(Writer&& other) = delete;
	
public:
	static Writer& GetInstance() {
		static Writer m_instance;
		return m_instance;
	};

	int writetofile(std::string text);
	int writetofile(std::string path, std::string text);

	void setpath(const std::string& path);
	bool open_for_write();

private:
	static Writer _Instance;
	std::ofstream ofs{};
	std::string path="";
};

