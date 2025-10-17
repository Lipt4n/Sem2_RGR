#pragma once
#include <vector>

using byte_array = std::vector<unsigned char>;

enum class ModeType {
    ENCRYPT = 1,
    DECRYPT = 2,
    EXIT = 0
};

enum class CipherType {
    GRONSFELD = 1,
    VERNAM = 2,
    SCYTALE = 3
};
