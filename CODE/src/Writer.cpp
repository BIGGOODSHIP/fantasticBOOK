#include "pch.h"
#include "Writer.h"

namespace {
	bool PathExists(const std::string& path) {
		return GetFileAttributesA(path.c_str()) != INVALID_FILE_ATTRIBUTES;
	}
}

Writer::~Writer() {
	discard_pending_write();
}

void Writer::discard_pending_write() {
	if (ofs.is_open()) {
		ofs.close();
	}

	ofs.clear();
	if (!tempPath.empty() && PathExists(tempPath)) {
		DeleteFileA(tempPath.c_str());
	}
	tempPath.clear();
	transactionOpen = false;
}

void Writer::setpath(const std::string& path) {
	discard_pending_write();
	this->path = path;
}

bool Writer::writetofile(const std::string& text) {
	if (!ofs.is_open()) {
		return false;
	}

	ofs << text << "\n";
	return ofs.good();
}

bool Writer::writetofile(
	const std::string& path,
	const std::string& text) {
	setpath(path);
	return open_for_write()
		&& writetofile(text)
		&& commit();
}

bool Writer::open_for_write() {
	discard_pending_write();
	if (path.empty()) {
		return false;
	}

	tempPath = path + ".tmp";
	ofs.open(tempPath, std::ios::out | std::ios::trunc);
	transactionOpen = ofs.is_open();
	if (!transactionOpen) {
		tempPath.clear();
	}
	return transactionOpen;
}

bool Writer::commit() {
	if (!transactionOpen || !ofs.is_open()) {
		return false;
	}

	ofs.flush();
	const bool writeSucceeded = ofs.good();
	ofs.close();
	const bool closeSucceeded = !ofs.fail();
	ofs.clear();

	if (!writeSucceeded || !closeSucceeded) {
		discard_pending_write();
		return false;
	}

	const std::string backupPath = path + ".bak";
	const bool targetExists = PathExists(path);
	if (targetExists) {
		DeleteFileA(backupPath.c_str());
		if (!ReplaceFileA(
			path.c_str(),
			tempPath.c_str(),
			backupPath.c_str(),
			REPLACEFILE_WRITE_THROUGH,
			nullptr,
			nullptr)) {
			discard_pending_write();
			return false;
		}
	}
	else {
		if (!MoveFileExA(
			tempPath.c_str(),
			path.c_str(),
			MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
			discard_pending_write();
			return false;
		}
	}

	tempPath.clear();
	transactionOpen = false;
	DeleteFileA(backupPath.c_str());
	return true;
}
