#include "Arcive.h"

bool Map::keyExist(string key)
{
	int index = -1;
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] == key) {
			index = i;
			break;
		}
	}
	return index > -1;
}

void Map::add(string key, string value)
{
	keys.push_back(key);
	values.push_back(value);
}

void Map::del(string key)
{
	int index = -1;
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] == key) {
			index = i;
			break;
		}
	}
	if (index > -1) {
		keys.erase(keys.begin() + index);
		values.erase(values.begin() + index);
	}
	else {
		throw "ќшибка удалени€ из архива. Ёлемента " + key + " уже в нем нет.";
	}
}

string Map::get(string key)
{
	int index = -1;
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] == key) {
			index = i;
			break;
		}
	}
	if (index > -1) {
		return values[index];
	}
	else {
		throw ("ќшибка получени€ данных из архива. Ёлемента " + key + " не был найден.").c_str();
	}
}

vector<string> Map::getKeys()
{
	return keys;
}

void Map::change(string key, string value)
{
	int index = -1;
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] == key) {
			index = i;
			break;
		}
	}
	if (index > -1) {
		values[index] = value;
	}
	else {
		throw "ќшибка изменени€ данных в архиве. Ёлемент " + key + " не был найден.";
	}
}

void Archive::createMap()
{
	fstream inFile;
	string line = "1", temp;
	inFile.open(arcivePath);
	while ((line != "##" && line != "")) {
		getline(inFile, line);
		if (line == "Files") {
			getline(inFile, line);
			while (line != "#") {
				archive.keys.push_back(line);
				getline(inFile, line);
			}
		} else if (line == "Content") {
			getline(inFile, line);
			while (line != "#") {
				temp = "";
				while (line != "^") {
					temp = temp + line + "\n";
					getline(inFile, line);
				}
				temp = temp.substr(0, temp.size() - 1);
				archive.values.push_back(temp);
				getline(inFile, line);
			}
		} else if (line == "Log") {
			getline(inFile, line);
			temp = "";
			while (line != "#") {
				temp = temp + line + "\n";
				getline(inFile, line);
			}
			ofstream out;
			out.open("D:\\Leo's\\Projects\\GitHub\\OS_Lab4\\Lab4\\\LogBook\\Log.txt", std::ofstream::out | std::ofstream::trunc);
			temp = temp.substr(0, temp.size() - 1);
			out << temp;
			out.close();
		}
	}
}

void Archive::uploadMap()
{
	ofstream out;
	out.open(arcivePath, std::ofstream::out | std::ofstream::trunc);
	out << "Files" << endl;
	for (int i = 0; i < archive.keys.size(); i++) {
		out << archive.keys[i] << endl;
	}
	out << "#" << endl;
	out << "Content" << endl;
	for (int i = 0; i < archive.values.size(); i++) {
		out << archive.values[i] << endl;
		out << "^" << endl;
	}
	out << "#" << endl;
	out << "Log" << endl;
	fstream in;
	string line, temp;
	in.open("D:\\Leo's\\Projects\\GitHub\\OS_Lab4\\Lab4\\\LogBook\\Log.txt");
	while (getline(in, line)) {
		temp = temp + line + "\n";
	}
	out << temp << endl << "#" << endl << "##" << endl;
	out.close();
}

bool Archive::checkStatus(string filePath, bool exist)
{
	string line, str_in;
	ifstream inFile;
	inFile.open(Path + filePath);
	while (getline(inFile, line)) {
		str_in = str_in + line + "\n";
	}

	if (archive.keyExist(filePath)) {
		return archive.get(filePath) == str_in;
	}
	else {
		return !exist;
	}

		
}

void Archive::deleteFile(string filePath)
{
	archive.del(filePath);
}

void Archive::addFile(string filePath)
{
	string line, str_in;
	ifstream inFile;
	inFile.open(Path + filePath);
	while (getline(inFile, line)) {
		str_in = str_in + line + "\n";
	}

	archive.add(filePath, str_in);
}

void Archive::changeFileName(string filePath_old, string filePath_new)
{
	archive.add(filePath_new, archive.get(filePath_old));
	archive.del(filePath_old);
}

void Archive::uploadData(string filePath)
{
	string line, str_in;
	ifstream inFile;
	inFile.open(Path + filePath);
	while (getline(inFile, line)) {
		str_in = str_in + line + "\n";
	}

	archive.change(filePath, str_in);
}

void Archive::recoverData(string filePath, bool exist)
{
	if (archive.keyExist(filePath)) {
		ofstream out;
		out.open(Path + filePath);
		out << archive.get(filePath);
		out.close();
	}
	else {
		if (exist) {
			remove((Path + filePath).c_str());
		} else {
			ofstream oFile(Path + filePath);

			oFile.open(Path + filePath);
			oFile << archive.get(filePath);
			oFile.close();
		}
	}
}