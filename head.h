#pragma once

enum class CipherType;

CipherType choose();

void encrypt();

void decrypt();

std::wstring GronsfeldEncrypt(const std::wstring& plain, const std::wstring& key);

std::wstring GronsfeldDecrypt(const std::wstring& cipher, const std::wstring& key);