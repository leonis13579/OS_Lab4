#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <direct.h>
#include <time.h>
#include <Windows.h>
#include <iomanip>
#include "Arcive.h"

using namespace std;
class Source {
private:
	string Path = "D:\\Leo's\\Projects\\GitHub\\OS_Lab4\\Lab4\\\LogBook\\Files\\";
	string LogBook = "D:\\Leo's\\Projects\\GitHub\\OS_Lab4\\Lab4\\\LogBook\\Log.txt";
	SYSTEMTIME time;

	enum MessageType {
		Debug,
		Warning,
		Error,
		Success
	};
	inline const char* ToString(MessageType v) {
		switch (v)
		{
		case Source::Debug:		return "Debug";
		case Source::Warning:	return "Warning";
		case Source::Error:		return "Error";
		case Source::Success:	return "Success";
		default:				return "[Unknown Message_Type]";
		}
	}

	void checkAndRecover(string filePath, bool exist);

public:
	Archive Archive;

	void menu();
	void deleteFile();
	bool isFileExist(string filePath);
	void createFile();
	void changeFileName();
	void writeToFile();
	void readFromFile();
	void init();
	void messageToLog(MessageType type, string msg);
	void uploadAchiveToFile();
};