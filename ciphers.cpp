#include <iostream>
#include "types.hpp"

using namespace std;

byte_array GronsfeldEncrypt(const byte_array& plain_text, const byte_array& key) {
    cout << "Процесс запущен!" << endl;
    cout << "Прогресс: ";
    size_t one_block = plain_text.size() / 10;
    size_t progress = 0;
    byte_array cipher_text(plain_text.size());
    for (size_t i = 0; i < plain_text.size(); i++) {
        cipher_text[i] = (plain_text[i] + key[i % key.size()]) % 256; 
        if (one_block != 0 && i / one_block != progress) {
            progress += 1;
            cout << "■";
        }
    }
    if (one_block == 0) {
        cout << "■■■■■■■■■■";
    }
    cout << endl << "Процесс успешно завершен!" << endl;
    return cipher_text;
}

byte_array GronsfeldDecrypt(const byte_array& cipher_text, const byte_array& key) {
    cout << "Запущено дешифрование!" << endl;
    cout << "Прогресс: ";
    size_t one_block = cipher_text.size() / 10;
    size_t progress = 0;
    byte_array plain_text(cipher_text.size());
    for (size_t i = 0; i < cipher_text.size(); i++) {
        plain_text[i] = (cipher_text[i] - key[i % key.size()] + 256) % 256; 
        if (one_block != 0 && i / one_block != progress) {
            progress += 1;
            cout << "■";
        }
    }
    if (one_block == 0) {
        cout << "■■■■■■■■■■";
    }
    cout << endl << "Дешифрование успешно завершено!" << endl;
    return plain_text;
}

byte_array Vernam(const byte_array& first_text, const byte_array& key) {
    cout << "Процесс запущен!" << endl;
    cout << "Прогресс: ";
    size_t one_block = first_text.size() / 10;
    size_t progress = 0;
    byte_array second_text(first_text.size());
    for (size_t i = 0; i < first_text.size(); i++) {
        second_text[i] = first_text[i] ^ key[i]; 
        if (one_block != 0 && i / one_block != progress) {
            progress += 1;
            cout << "■";
        }
    }
    if (one_block == 0) {
        cout << "■■■■■■■■■■";
    }
    cout << endl << "Процесс успешно завершен!" << endl;
    return second_text;
}

byte_array ScytaleEncrypt(const byte_array& plain_text, const byte_array& key) {
    cout << "Процесс запущен!" << endl;
    size_t rows = key[0];
    size_t length = plain_text.size();
    size_t columns = (length + rows - 1) / rows;
    size_t remainder = length % rows;
    vector<vector<unsigned char>> table(rows);
    for (size_t r = 0; r < rows; r++) {
        table[r].resize(columns - (r < remainder ? 0 : 1));
    }
    size_t index = 0;
    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < table[r].size(); c++) {
            table[r][c] = plain_text[index++];
        }
    }
    byte_array cipher_text(length);
    index = 0;
    for (size_t c = 0; c < columns; c++) {
        for (size_t r = 0; r < rows; r++) {
            if (c < table[r].size()) {
                cipher_text[index++] = table[r][c];
            }

        }
    }
    cout << endl << "Процесс успешно завершен!" << endl;
    return cipher_text;
}

byte_array ScytaleDecrypt(const byte_array& cipher_text, const byte_array& key) {
    cout << "Процесс запущен!" << endl;
    size_t rows = key[0];
    size_t length = cipher_text.size();
    size_t columns = (length + rows - 1) / rows;
    size_t remainder = length % rows;
    vector<vector<unsigned char>> table(rows);
    for (size_t r = 0; r < rows; r++) {
        table[r].resize(columns - (r < remainder ? 0 : 1));
    }
    size_t index = 0;
    for (size_t c = 0; c < columns; c++) {
        for (size_t r = 0; r < rows; r++) {
            if (c < table[r].size()) {
                table[r][c] = cipher_text[index++];
            }
        }
    }
    byte_array plain_text(length);
    index = 0;
    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < table[r].size(); c++) {
            plain_text[index++] = table[r][c];
        }
    }
    cout << endl << "Процесс успешно завершен!" << endl;
    return plain_text;
}

byte_array EncryptDecrypt(const ModeType& mode, const CipherType& cipher, const byte_array& text, const byte_array& key) {
    byte_array result;
    switch (mode) {
        case (ModeType::ENCRYPT): {
            switch (cipher) {
                case (CipherType::GRONSFELD): {
                    result = GronsfeldEncrypt(text, key);
                    break;
                }
                case (CipherType::VERNAM): {
                    result = Vernam(text, key);
                    break;
                }
                case (CipherType::SCYTALE): {
                    result = ScytaleEncrypt(text, key);
                    break;
                }
            }
            break;
        }
        case (ModeType::DECRYPT): {
            switch (cipher) {
                case (CipherType::GRONSFELD): {
                    result = GronsfeldDecrypt(text, key);
                    break;
                }
                case (CipherType::VERNAM): {
                    result = Vernam(text, key);
                    break;
                }
                case (CipherType::SCYTALE): {
                    result = ScytaleDecrypt(text, key);
                    break;
                }
            }
            break;
        }
        case (ModeType::EXIT): {
            break;
        }
    }
    return result;
}