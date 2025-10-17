#pragma once
#include "types.hpp"

byte_array ReadFileToBytearray();

void SaveBytearrayToFile(const byte_array& data, const std::string& hint);