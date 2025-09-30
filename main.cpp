#include "iostream"
#include "stdexcept"
#include "head.h"

using namespace std;

enum class CmdType {
    ENCRYPT = 1,
    DECRYPT = 2,
    EXIT = 0
};

int main() {
    while (true) {
        int userInput = -1;
        system("clear");
        cout << "========== МЕНЮ ==========" << endl;
        cout << "Добро пожаловать!" << endl << endl;
        cout << "Выберите действие:" << endl;
        cout << "1. Шифрование" << endl;
        cout << "2. Дешифрование" << endl;
        cout << "0. Выход" << endl;
        while (true) {
            try {
                cout << "   Ввод > ";
                cin >> userInput;
                if (userInput >= 0 && userInput <= 2) {
                    break;
                } else {
                    throw invalid_argument("Некорректный ввод!");
                }
            } catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
                cin.clear();
                cin.ignore(256, '\n');
            }
        }
        auto userCmd = static_cast<CmdType>(userInput);
        switch (userCmd) {
            case CmdType::ENCRYPT: {
                encrypt();
                break;
            }
            case CmdType::DECRYPT: {
                decrypt();
                break;
            }
            case CmdType::EXIT: {
                return 0;
            }
        }
    }
}

