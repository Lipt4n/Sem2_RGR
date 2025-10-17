#include <iostream>
#include <string>
#include "utils.hpp"
#include "types.hpp"

using namespace std;

void ClearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int GetMin(const int& a, const int& b) {
    if (a > b) {
        return b;
    } else {
        return a;
    }
}

string NameOfCipher(CipherType cipher) {
    switch (cipher) {
        case (CipherType::GRONSFELD): {
            return "Гронсфельда";
        }
        case (CipherType::VERNAM): {
            return "Вернама";
        }
        case (CipherType::SCYTALE): {
            return "Скитала";
        }
    }
}

string DisplayKey(CipherType cipher, byte_array key) {
    switch (cipher) {
        case (CipherType::GRONSFELD): {
            string res;
            for (int n : key) {
                res += to_string(n);
            }
            return res;
        }
        case (CipherType::VERNAM): {
            string res;
            for (int i = 0; i < GetMin(20, key.size()); i++) {
                res += to_string(key[i]) + " ";
            }
            res += "...";
            return res;
        }
        case (CipherType::SCYTALE): {
            return to_string(key[0]);
        }
    }
}

int GetIntInput(const string& prompt, const int& min, const int& max) {
    int value;
    while (true) {
        try {
            cout << "   " << prompt << " > ";
            if (!(cin >> value)) {
                throw invalid_argument("Некорректный ввод!");
            } else if (value < min || value > max) {
                throw invalid_argument("Введённое значение должно быть от " + to_string(min) + " до " + to_string(max) + "!");
            }
            break;
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
            ClearCin();
        }
    }
    return value;
}