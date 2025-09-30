#include "iostream"
#include "head.h"

using namespace std;

enum class CipherType {
    GRONSFELD = 1,
    PLAYFAIR = 2,
    VERNAM = 3,
    SCYTALE = 4,
    EXIT = 0
};

CipherType choose_cipher() {
    int userInput;
    system("clear");
    cout << "========== ВЫБОР ШИФРА ==========" << endl << endl;
    cout << "Выберите шифр для работы:" << endl;
    cout << "1. Гронсфельда" << endl;
    cout << "2. Плейфера" << endl;
    cout << "3. Вернама" << endl;
    cout << "4. Скитала" << endl;
    cout << "0. Назад" << endl;
    while (true) {
        try {
            cout << "   Ввод > ";
            cin >> userInput;
            if (userInput < 0 || userInput > 4) {
                throw invalid_argument("Некорректный ввод!");
            } else {break;}
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
            cin.clear();
			cin.ignore(256, '\n');
        }
    }
    return static_cast<CipherType>(userInput);
}

void encrypt() {
    auto userCipher = choose_cipher();
    switch (userCipher) {
        case CipherType::GRONSFELD: {
            break;
        }
        case CipherType::PLAYFAIR: {
            break;
        }
        case CipherType::VERNAM: {
            break;
        }
        case CipherType::SCYTALE: {
            break;
        }        
        case CipherType::EXIT: {
            return;
        }
    }
}

void decrypt() {
    auto userCipher = choose_cipher();
    switch (userCipher) {
        case CipherType::GRONSFELD: {
            break;
        }
        case CipherType::PLAYFAIR: {
            break;
        }
        case CipherType::VERNAM: {
            break;
        }
        case CipherType::SCYTALE: {
            break;
        }        
        case CipherType::EXIT: {
            return;
        }
    }
}