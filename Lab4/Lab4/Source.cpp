#include "Source.h"
#include <filesystem>

using namespace std;

void Source::checkAndRecover(string filePath, bool exist)
{
    if (!Archive.checkStatus(filePath, exist)) {
        messageToLog(Error, "@������������ ������ � �������. ����� ��������� ��������� �������������.");

        Archive.recoverData(filePath, exist);

        throw "������������ ������ � �������. ����� ��������� ��������� �������������.";
    }
}

void Source::menu()
{
    cout << "1. ������� ����." << endl;
    cout << "2. ������������� ����" << endl;
    cout << "3. �������� ����� � ����" << endl;
    cout << "4. ���������� ���������� �����" << endl;
    cout << "5. ������� ����" << endl;
    cout << "6. ���������� ���������" << endl;
}

void Source::deleteFile()
{
    string fileName;
    messageToLog(Debug, "@������ �� �������� � �����.");
    system("CLS");
    cout << "����� \"�������� �����\"" << endl << endl << "������� �������� ����� c �����������." << endl << ">> ";
    while (fileName == "" || fileName == "\n") {
        getline(cin, fileName);
    }
    if (!isFileExist(Path + fileName)) {
        messageToLog(Warning, "@���� � ��������� " + fileName + " �� ����������.");
        cout << "� ���������, ���� � ����� ��������� �� ����������. ������ �������� ������ (Y) ��� ����� � ���� (N)?" << endl << ">> ";
        string answ;
        while (answ == "" || answ == "\n") {
            getline(cin, answ);
        }
        system("CLS");
        if (answ == "Y" || answ == "y") {
            deleteFile();
        }
        return;
    }
    checkAndRecover(fileName, true);

    messageToLog(Debug, "@�������� ����� " + fileName);
    remove((Path + fileName).c_str());
    Sleep(5000);

    if (!isFileExist(Path + fileName)) {
        messageToLog(Success, "@���� � ��������� " + fileName + " ������� ������.");
        Archive.deleteFile(fileName);
        system("CLS");
    }
    else {
        messageToLog(Error, "@��������� ������ ��� �������� ����� � ��������� " + fileName + ".");
        system("CLS");
    }
}

bool Source::isFileExist(string filePath)
{
    bool isExist = false;
    std::ifstream fin(filePath.c_str());

    if (fin.is_open())
        isExist = true;

    fin.close();
    return isExist;
}

void Source::createFile()
{
    string fileName;
    messageToLog(Debug, "@������ �� �������� �����.");
    system("CLS");
    cout << "����� \"�������� �����\"" << endl << endl << "������� �������� ����� c �����������." << endl << ">> " ;
    while (fileName == "" || fileName == "\n") {
        getline(cin, fileName);
    }
    if (isFileExist(Path + fileName)) {
        messageToLog(Warning, "@���� � ��������� " + fileName + " ��� ����������.");
        cout << "� ���������, ���� � ����� ��������� ��� ����������. ������ �������� ������ (Y) ��� ����� � ���� (N)?" << endl << ">> ";
        string answ;
        while (answ == "" || answ == "\n") {
            getline(cin, answ);
        }
        system("CLS");
        if (answ == "Y" || answ == "y") {
            createFile();
        }
        return;
    }
    checkAndRecover(fileName, false);

    ofstream oFile(Path + fileName);
    Sleep(5000);
    if (isFileExist(Path + fileName)) {
        messageToLog(Success, "@���� � ��������� " + fileName + " ������� ������.");
        Archive.addFile(fileName);
        system("CLS");
    }
    else {
        messageToLog(Error, "@��������� ������ ��� �������� ���� � ��������� " + fileName + ".");
        system("CLS");
    }
}

void Source::changeFileName()
{
    string fileName_old;
    string fileName_new;
    messageToLog(Debug, "@������ �� ��������� �����.");
    system("CLS");
    cout << "����� \"������������ �����\"" << endl << endl << "������� �������� ����� c �����������." << endl << ">> ";
    while (fileName_old == "" || fileName_old == "\n") {
        getline(cin, fileName_old);
    }
    if (!isFileExist(Path + fileName_old)) {
        messageToLog(Warning, "@���� � ��������� " + fileName_old + " �� ����������.");
        cout << "� ���������, ���� � ����� ��������� �� ����������. ������ �������� ������ (Y) ��� ����� � ���� (N)?" << endl << ">> ";
        string answ;
        while (answ == "" || answ == "\n") {
            getline(cin, answ);
        }
        system("CLS");
        if (answ == "Y" || answ == "y") {
            changeFileName();
        }
        return;
    }
    checkAndRecover(fileName_old, true);
    cout << "������� ����� �������� ����� c �����������." << endl << ">> ";
    while (fileName_new == "" || fileName_new == "\n") {
        getline(cin, fileName_new);
    }
    if (isFileExist(Path + fileName_new)) {
        messageToLog(Warning, "@���� � ��������� " + fileName_new + " ��� ����������.");
        cout << "� ���������, ���� � ����� ��������� ��� ����������. ������ �������� ������ (Y) ��� ����� � ���� (N)?" << endl << ">> ";
        string answ;
        while (answ == "" || answ == "\n") {
            getline(cin, answ);
        }
        system("CLS");
        if (answ == "Y" || answ == "y") {
            changeFileName();
            return;
        }
    }


    rename((Path + fileName_old).c_str(), (Path + fileName_new).c_str());
    Sleep(5000);

    if (isFileExist(Path + fileName_new) && !isFileExist(Path + fileName_old)) {
        messageToLog(Success, "@���� ������� ������������.");
        Archive.changeFileName(fileName_old, fileName_new);
        system("CLS");
    }
    else {
        messageToLog(Error, "@��������� ������ ��� �������������� �����.");
        system("CLS");
    }
}

void Source::writeToFile()
{
    string fileName;
    messageToLog(Debug, "@������ �� ������ � ����.");
    system("CLS");
    cout << "����� \"������ � ����\"" << endl << endl << "������� �������� ����� c �����������." << endl << ">> ";
    while (fileName == "" || fileName == "\n") {
        getline(cin, fileName);
    }
    if (!isFileExist(Path + fileName)) {
        messageToLog(Warning, "@���� � ��������� " + fileName + " �� ����������.");
        cout << "� ���������, ���� � ����� ��������� �� ����������. ������ �������� ������ (Y) ��� ����� � ���� (N)?" << endl << ">> ";
        string answ;
        while (answ == "" || answ == "\n") {
            getline(cin, answ);
        }
        system("CLS");
        if (answ == "Y" || answ == "y") {
            writeToFile();
        }
        return;
    }
    checkAndRecover(fileName, true);

    messageToLog(Debug, "@������ � ���� " + fileName);
    string prev;
    ifstream inFile;
    inFile.open(Path + fileName);
    string line;
    while (getline(inFile, line)) {
        prev = prev + line + "\n";
    }
    //prev = prev.substr(0, prev.size() - 2);
    inFile.close();

    cout << "������� ����� ����������� ��� �������� � ����: (����� ������ - #)" << endl;
    string msg;
    while (msg == "" || msg == "\n") {
        getline(cin, msg, '#');
    }
    ofstream out;
    out.open(Path + fileName, ios::app);
    out << msg;
    out.close();
    string t_str = msg.substr(msg.size() - 1, msg.size());
    if (msg.substr(msg.size() - 1, msg.size()) == "\n") {
        msg = msg.substr(0, msg.size() - 1);
    }

    Sleep(5000);

    string str_res;
    inFile.open(Path + fileName);
    while (getline(inFile, line)) {
        str_res = str_res + line + "\n";
    }
    str_res = str_res.substr(0, str_res.size() - 1);
    bool result = (prev + msg == str_res);

    if (isFileExist(Path + fileName) && result) {
        messageToLog(Success, "@���������� ������� �������� � ����.");
        Archive.uploadData(fileName);
        system("CLS");
    }
    else {
        messageToLog(Error, "@��������� ������ ��� ������ � ����.");
        system("CLS");
    }
}

void Source::readFromFile()
{
    string fileName;
    messageToLog(Debug, "@������ �� ������ �� �����.");
    system("CLS");
    cout << "����� \"������ �� �����\"" << endl << endl << "������� �������� ����� c �����������." << endl << ">> ";
    while (fileName == "" || fileName == "\n") {
        getline(cin, fileName);
    }
    if (!isFileExist(Path + fileName)) {
        messageToLog(Warning, "@���� � ��������� " + fileName + " �� ����������.");
        cout << "� ���������, ���� � ����� ��������� �� ����������. ������ �������� ������ (Y) ��� ����� � ���� (N)?" << endl << ">> ";
        string answ;
        while (answ == "" || answ == "\n") {
            getline(cin, answ);
        }
        system("CLS");
        if (answ == "Y" || answ == "y") {
            readFromFile();
        }
        return;
    }
    checkAndRecover(fileName, true);

    messageToLog(Debug, "@������ �� ����� " + fileName);
    string line, str_in;
    ifstream inFile;
    inFile.open(Path + fileName);

    cout << endl << "���������� �����: " << endl;
    while (getline(inFile, line)) {
        str_in = str_in + line + "\n";
    }
    cout << str_in << endl;
    inFile.close();
    system("pause");

    Sleep(2500);
    string str_res;
    inFile.open(Path + fileName);
    while (getline(inFile, line)) {
        str_res = str_res + line + "\n";
    }
    inFile.close();
    if (str_in == str_res && isFileExist(Path + fileName)) {
        messageToLog(Success, "@������ �� ����� ��������� �������.");
        Archive.uploadData(fileName);
        system("CLS");
    }
    else {
        messageToLog(Error, "@��������� ������ ��� ������ �� �����.");
        system("CLS");
    }
}

void Source::init()
{
    string temp_command = "mkdir " + Path;
    system(temp_command.c_str());
    system("CLS");
    if (!isFileExist(LogBook)) {
        ofstream oFile(LogBook);
    }
    Archive.createMap();
}

void Source::messageToLog(MessageType type, string msg)
{
    GetLocalTime(&time);
    ofstream out;
    out.open(LogBook, ofstream::out | ofstream::app);
    if (out.is_open()) {
        out << setw(2) << setfill('0') << time.wDay << "." << setw(2) << setfill('0') << time.wMonth;
        out << "." << time.wYear << " ";
        out << setw(2) << setfill('0') << time.wHour << ":" << setw(2) << setfill('0') << time.wMinute << ":" << setw(2) << setfill('0') << time.wSecond;
        out << " " << "\t" << left << setw(8) << setfill(' ') << ToString(type) << "\t" << msg << endl;
    }
    else {
        throw "���������� ������� ������ ��� ������.";
    }
    out.close();
}

void Source::uploadAchiveToFile()
{
    messageToLog(Debug, "@�������� ������ � �����.");
    Archive.uploadMap();
}
