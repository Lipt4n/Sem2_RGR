#include "types.hpp"
#include "utils.hpp"
#include "file_io.hpp"
#include "get_keys.hpp"
#include <iostream>
#include <random>

using namespace std;

byte_array InputKey(const CipherType& Cipher, const size_t& size_of_file) {
    byte_array key_in_array;
    int key;
    switch (Cipher) {
        case CipherType::GRONSFELD: {
            cout << "Выбран шифр Гронсфельда, введите любое число >100" << endl;
            key = GetIntInput("Ввод", 100, 999999999);
            while (key > 0) {
                key_in_array.push_back(key % 10);
                key /= 10;
            }
            reverse(key_in_array.begin(), key_in_array.end());
            break;
        }
        case CipherType::VERNAM: {
            cout << "Выбран шифр Вернама, вводите число от 0 до 255 на каждый байт файла хаха (" << size_of_file << " байт)" << endl;
            for (int i = 0; i < size_of_file; i++) {
                key = GetIntInput("Введите число для байта " + to_string(i), 0, 255);
                key_in_array.push_back(key);
            }
        }
        case CipherType::SCYTALE: {
            cout << "Выбран шифр Скитала, введите любое число >0 и <" << GetMin(255, size_of_file) << endl;
            key = GetIntInput("Ввод", 1, GetMin(255, size_of_file));
            key_in_array.push_back(key);
            break;
        }
    }
    return key_in_array;
}

byte_array ReadKey(const CipherType& Cipher, const size_t& size_of_file) { 
    byte_array key;
    while (true) {
        try {
            key = ReadFileToBytearray();
            switch (Cipher) {
                case(CipherType::GRONSFELD): {
                    if (key.size() > 9 || key.size() < 3) {
                        throw runtime_error("Данный файл не годится в качестве ключа!");
                    }
                    for (auto& i : key) {
                        if (i > 9) {
                            throw runtime_error("Данный файл не годится в качестве ключа!");
                        }
                    }
                    break;
                }
                case(CipherType::VERNAM): {
                    if (!(key.size() == size_of_file)) {
                        throw runtime_error("Данный файл не годится в качестве ключа!");
                    }
                    break;
                }
                case(CipherType::SCYTALE): {
                    if (!(key.size() == 1)) {
                        throw runtime_error("Данный файл не годится в качестве ключа!");
                    }
                    if (key[0] == 0 || key[0] > size_of_file) {
                        throw runtime_error("Данный файл не годится в качестве ключа!");
                    }
                    break;
                }
            }
            break;
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }
    return key;
}

byte_array GenKey(const CipherType& Cipher, const size_t& size_of_file) {
    byte_array key_in_array;
    random_device rd;
    mt19937 gen(rd());
    switch (Cipher) {
        case CipherType::GRONSFELD: {
            uniform_int_distribution<> length_distribution(3,9);
            uniform_int_distribution<> value_distribution(1,9);
            size_t key_length = length_distribution(gen);
            key_in_array.resize(key_length);
            cout << "Сгенерированный ключ: ";
            for (size_t i = 0; i < key_length; i++) {
                key_in_array[i] = value_distribution(gen);
                cout << int(key_in_array[i]);
            }
            cout << endl;
            break;
        }
        case CipherType::VERNAM: {
            uniform_int_distribution<> value_distribution(0,255);
            key_in_array.resize(size_of_file);
            cout << "Сгенерированный ключ:";
            for (int i = 0; i < size_of_file; i++) {
                key_in_array[i] = value_distribution(gen);
                if (i < 20) {
                    cout << " " << int(key_in_array[i]);
                }
            }
            cout << " ... Сохраните в файл!" << endl;
            break;
        }
        case CipherType::SCYTALE: {
            uniform_int_distribution<> value_distribution(1, GetMin(255, size_of_file));
            key_in_array.resize(1);
            key_in_array[0] = value_distribution(gen);
            cout << "Сгенерированный ключ: " << int(key_in_array[0]) << endl;
            break;
        }
    }
    return key_in_array;
}

byte_array GetKey(const ModeType& Mode, const CipherType& Cipher, const size_t& size_of_file) {
    system("clear");
    cout << "========== ВЫБОР КЛЮЧА ==========" << endl << endl;
    cout << "Выберите источник ключа:" << endl;
    cout << "1. Ввести*" << endl;
    cout << "2. Из файла (bin)";
    cout << ((Mode == ModeType::ENCRYPT) ? "\n3. Сгенерировать" : "") << endl;
    cout << "* - Если у вас выбран шифр Вернама, вам придется вводить число 0-255 на каждый байт файла." << endl;
    int source_of_key = GetIntInput("Выбор", 1, (Mode == ModeType::ENCRYPT) ? 3 : 2);
    switch (source_of_key) {
        case 1: {
            byte_array key = InputKey(Cipher, size_of_file);
            if (Mode == ModeType::ENCRYPT) {
                SaveBytearrayToFile(key, "ключ");    
            }
            return key;
        }
        case 2: {
            return ReadKey(Cipher, size_of_file);
        }
        case 3: {
            byte_array key = GenKey(Cipher, size_of_file);
            if (Mode == ModeType::ENCRYPT) {
                SaveBytearrayToFile(key, "ключ");    
            }
            return key;
        }
    }
    return {};
}