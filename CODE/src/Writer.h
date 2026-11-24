#pragma once
#include<iostream>
#include<fstream>
#include<string>
//对外输出工具类
//往外写内容到指定文件
class Writer
{
private:
	Writer() {};
public:

	~Writer();

	Writer(const Writer& other) = delete;
	Writer(Writer&& other) = delete;
	Writer& operator=(const Writer& other) = delete;
	Writer& operator=(Writer&& other) = delete;
	
public:
	static Writer& GetInstance() {
		static Writer m_instance;
		return m_instance;
	};

	bool writetofile(const std::string& text);
	bool writetofile(const std::string& path, const std::string& text);

	void setpath(const std::string& path);
	bool open_for_write();
	bool commit();

private:
	void discard_pending_write();

	std::ofstream ofs{};
	std::string path{};
	std::string tempPath{};
	bool transactionOpen = false;
};

