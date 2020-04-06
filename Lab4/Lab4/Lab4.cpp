#include "Source.h"
#include <Windows.h>


using namespace std;

void MainLogic() {
    Source source;
    int choose;

    try {
        source.init();

        do {
            source.menu();
            cin >> choose;

            switch (choose)
            {
            case 1:
                source.createFile();
                break;
            case 2:
                source.changeFileName();
                break;
            case 3:
                source.writeToFile();
                break;
            case 4:
                source.readFromFile();
                break;
            case 5:
                source.deleteFile();
                break;
            case 6:
                source.uploadAchiveToFile();
                break;
            default:
                cout << "¬ведено некорректное значение. ¬ведите пор€дковый номер интересующего вас пункта." << endl;
                break;
            }
        } while (choose != 6);
    }
    catch (const char* e) {
        cout << e << endl;
        system("pause");
        source.Archive.uploadMap();
        system("CLS");
        MainLogic();
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    MainLogic();
}
