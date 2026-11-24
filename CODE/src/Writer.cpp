#include "pch.h"
#include "Writer.h"

void Writer::setpath(const std::string& path) {
	if (ofs.is_open()) {
		ofs.close();
	}

	ofs.clear();
	this->path = path;
}

int Writer::writetofile(std::string text) {
	if (!ofs.is_open()) {
		ofs.open(path, std::ios::out | std::ios::trunc);
		if (!ofs.is_open()) {
			return -1;
		}
	}
	ofs << text << "\n";
	return 1;
}

int Writer::writetofile(std::string path,std::string text) {
	if (!ofs.is_open()) {
		ofs.open(path, std::ios::out | std::ios::trunc);
		if (!ofs.is_open()) {
			return -1;
		}
	}
	ofs << text << "\n";
	return 1;
}

bool Writer::open_for_write() {
	if (!ofs.is_open()) {
		ofs.open(path);
		if (!ofs.is_open()) {
			return -1;
		}
	}
}