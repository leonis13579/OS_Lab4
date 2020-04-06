#include "Source.h"
#include <filesystem>

using namespace std;

void Source::checkAndRecover(string filePath, bool exist)
{
    if (!Archive.checkStatus(filePath, exist)) {
        messageToLog(Error, "@Несовпадение данных с архивом. Будет применино резервное востановление.");

        Archive.recoverData(filePath, exist);

        throw "Несовпадение данных с архивом. Будет применино резервное востановление.";
    }
}

void Source::menu()
{
    cout << "1. Создать файл." << endl;
    cout << "2. Переименовать файл" << endl;
    cout << "3. Добавить текст в файл" << endl;
    cout << "4. Отобразить содержимое файла" << endl;
    cout << "5. Удалить файл" << endl;
    cout << "6. Завершение программы" << endl;
}

void Source::deleteFile()
{
    string fileName;
    messageToLog(Debug, "@Запрос на удаление в файла.");
    system("CLS");
    cout << "Режим \"Удаление файла\"" << endl << endl << "Введите название файла c расширением." << endl << ">> ";
    while (fileName == "" || fileName == "\n") {
        getline(cin, fileName);
    }
    if (!isFileExist(Path + fileName)) {
        messageToLog(Warning, "@Файл с названием " + fileName + " не существует.");
        cout << "К сожалению, файл с таким названием не существует. Ввести название заново (Y) или выйти в меню (N)?" << endl << ">> ";
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

    messageToLog(Debug, "@Удаление файла " + fileName);
    remove((Path + fileName).c_str());
    Sleep(5000);

    if (!isFileExist(Path + fileName)) {
        messageToLog(Success, "@Файл с названием " + fileName + " успешно удален.");
        Archive.deleteFile(fileName);
        system("CLS");
    }
    else {
        messageToLog(Error, "@Произошла ошибка при удалении файла с названием " + fileName + ".");
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
    messageToLog(Debug, "@Запрос на создание файла.");
    system("CLS");
    cout << "Режим \"Создание файла\"" << endl << endl << "Введите название файла c расширением." << endl << ">> " ;
    while (fileName == "" || fileName == "\n") {
        getline(cin, fileName);
    }
    if (isFileExist(Path + fileName)) {
        messageToLog(Warning, "@Файл с названием " + fileName + " уже существует.");
        cout << "К сожалению, файл с таким названием уже существует. Ввести название заново (Y) или выйти в меню (N)?" << endl << ">> ";
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
        messageToLog(Success, "@Файл с названием " + fileName + " успешно создан.");
        Archive.addFile(fileName);
        system("CLS");
    }
    else {
        messageToLog(Error, "@Произошла ошибка при создании файл с названием " + fileName + ".");
        system("CLS");
    }
}

void Source::changeFileName()
{
    string fileName_old;
    string fileName_new;
    messageToLog(Debug, "@Запрос на изменение файла.");
    system("CLS");
    cout << "Режим \"Переименовка файла\"" << endl << endl << "Введите название файла c расширением." << endl << ">> ";
    while (fileName_old == "" || fileName_old == "\n") {
        getline(cin, fileName_old);
    }
    if (!isFileExist(Path + fileName_old)) {
        messageToLog(Warning, "@Файл с названием " + fileName_old + " не существует.");
        cout << "К сожалению, файл с таким названием не существует. Ввести название заново (Y) или выйти в меню (N)?" << endl << ">> ";
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
    cout << "Введите новое название файла c расширением." << endl << ">> ";
    while (fileName_new == "" || fileName_new == "\n") {
        getline(cin, fileName_new);
    }
    if (isFileExist(Path + fileName_new)) {
        messageToLog(Warning, "@Файл с названием " + fileName_new + " уже существует.");
        cout << "К сожалению, файл с таким названием уже существует. Ввести название заново (Y) или выйти в меню (N)?" << endl << ">> ";
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
        messageToLog(Success, "@Файл успешно переименован.");
        Archive.changeFileName(fileName_old, fileName_new);
        system("CLS");
    }
    else {
        messageToLog(Error, "@Произошла ошибка при переименовании файла.");
        system("CLS");
    }
}

void Source::writeToFile()
{
    string fileName;
    messageToLog(Debug, "@Запрос на запись в файл.");
    system("CLS");
    cout << "Режим \"Запись в файл\"" << endl << endl << "Введите название файла c расширением." << endl << ">> ";
    while (fileName == "" || fileName == "\n") {
        getline(cin, fileName);
    }
    if (!isFileExist(Path + fileName)) {
        messageToLog(Warning, "@Файл с названием " + fileName + " не существует.");
        cout << "К сожалению, файл с таким названием не существует. Ввести название заново (Y) или выйти в меню (N)?" << endl << ">> ";
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

    messageToLog(Debug, "@Запись в файл " + fileName);
    string prev;
    ifstream inFile;
    inFile.open(Path + fileName);
    string line;
    while (getline(inFile, line)) {
        prev = prev + line + "\n";
    }
    //prev = prev.substr(0, prev.size() - 2);
    inFile.close();

    cout << "Введите текст необходимый для переноса в файл: (конец строки - #)" << endl;
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
        messageToLog(Success, "@Информация успешно записана в файл.");
        Archive.uploadData(fileName);
        system("CLS");
    }
    else {
        messageToLog(Error, "@Произошла ошибка при записи в файл.");
        system("CLS");
    }
}

void Source::readFromFile()
{
    string fileName;
    messageToLog(Debug, "@Запрос на чтение из файла.");
    system("CLS");
    cout << "Режим \"Чтение из файла\"" << endl << endl << "Введите название файла c расширением." << endl << ">> ";
    while (fileName == "" || fileName == "\n") {
        getline(cin, fileName);
    }
    if (!isFileExist(Path + fileName)) {
        messageToLog(Warning, "@Файл с названием " + fileName + " не существует.");
        cout << "К сожалению, файл с таким названием не существует. Ввести название заново (Y) или выйти в меню (N)?" << endl << ">> ";
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

    messageToLog(Debug, "@Чтение из файла " + fileName);
    string line, str_in;
    ifstream inFile;
    inFile.open(Path + fileName);

    cout << endl << "Содержание файла: " << endl;
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
        messageToLog(Success, "@Данные из файла прочитаны успешно.");
        Archive.uploadData(fileName);
        system("CLS");
    }
    else {
        messageToLog(Error, "@Произошла ошибка при чтения из файла.");
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
        throw "Невозможно открыть журнал для записи.";
    }
    out.close();
}

void Source::uploadAchiveToFile()
{
    messageToLog(Debug, "@Выгрузка данных в архив.");
    Archive.uploadMap();
}
