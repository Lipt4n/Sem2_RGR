#include <iostream>
#include <string>
#include <locale>

using namespace std;

wstring GronsfeldEncrypt(const wstring& plain, const wstring& key) {
    wstring cipher;
    cipher.reserve(plain.size());
    int K = key.size();
    for (size_t i = 0; i < plain.size(); ++i) {
        wchar_t c = plain[i];
        int shift = key[i % K] - L'0';

        // печатные ASCII 32..126
        if (c >= 32 && c <= 126) {
            wchar_t base = 32;
            int N = 126 - 32 + 1;
            int pos = c - base;
            cipher.push_back(wchar_t(base + (pos + shift) % N) );

        // Русский верхний (А..Я и Ё)
        } else if ((c >= L'А' && c <= L'Я') || c == L'Ё') {
            int pos = (c == L'Ё' ? 32 : c - L'А');
            int N = 33;
            int npos = (pos + shift) % N;
            cipher.push_back(npos == 32 ? L'Ё' : wchar_t(L'А' + npos) );

        // Русский нижний (а..я и ё)
        } else if ((c >= L'а' && c <= L'я') || c == L'ё') {
            int pos = (c == L'ё' ? 32 : c - L'а');
            int N = 33;
            int npos = (pos + shift) % N;
            cipher.push_back(npos == 32 ? L'ё' : wchar_t(L'а' + npos) );

        // всё остальное — без изменений
        } else {
            cipher.push_back(c);
        }
    }
    return cipher;
}

wstring GronsfeldDecrypt(const wstring& cipher, const wstring& key) {
    wstring plain;
    plain.reserve(cipher.size());
    int K = key.size();
    for (size_t i = 0; i < cipher.size(); ++i) {
        wchar_t c = cipher[i];
        int shift = key[i % K] - L'0';

        if (c >= 32 && c <= 126) {
            wchar_t base = 32;
            int N = 126 - 32 + 1;
            int pos = c - base;
            plain.push_back(wchar_t(base + (pos - shift + N) % N) );

        } else if ((c >= L'А' && c <= L'Я') || c == L'Ё') {
            int pos = (c == L'Ё' ? 32 : c - L'А');
            int N = 33;
            int npos = (pos - shift + N) % N;
            plain.push_back(npos == 32 ? L'Ё' : wchar_t(L'А' + npos) );

        } else if ((c >= L'а' && c <= L'я') || c == L'ё') {
            int pos = (c == L'ё' ? 32 : c - L'а');
            int N   = 33;
            int npos = (pos - shift + N) % N;
            plain.push_back(npos == 32 ? L'ё' : wchar_t(L'а' + npos) );

        } else {
            plain.push_back(c);
        }
    }
    return plain;
}

int main() {
    locale::global(locale("")); // Системная локаль
    wcin.imbue(locale());
    wcout.imbue(locale());

    wstring pt;
    getline(wcin, pt);
    wcout << L"Введённый текст: " << pt << endl;

    wstring key;
    getline(wcin, key);
    wcout << L"Введённый ключ: " << key << endl;

    wstring enc = GronsfeldEncrypt(pt, key);
    wcout << L"Зашифровано: " << enc << endl;

    wstring dec = GronsfeldDecrypt(enc, key);
    wcout << L"Расшифровано: " << dec << endl;
}
