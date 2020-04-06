#pragma once
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Map
{
	vector<string> keys;
	vector<string> values;
public:
	bool keyExist(string key);
	void add(string key, string value);
	void del(string key);
	string get(string key);
	vector<string> getKeys();
	void change(string key, string value);
};

class Archive {
	Map archive;
	string Log;
	string Path = "D:\\Leo's\\Projects\\GitHub\\OS_Lab4\\Lab4\\\LogBook\\Files\\";
	string arcivePath = "D:\\Leo's\\Projects\\GitHub\\OS_Lab4\\Lab4\\\LogBook\\Arcive.txt";
public:
	void createMap();
	void uploadMap();
	bool checkStatus(string filePath, bool exist);
	void deleteFile(string filePath);
	void addFile(string filePath);
	void changeFileName(string filePath_old, string filePath_new);
	void uploadData(string filePath);
	void recoverData(string filePath, bool exist);
};
