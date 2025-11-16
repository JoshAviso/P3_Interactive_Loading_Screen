#pragma once

#include <string>
using String = std::string;

inline String ToString(int val) { return std::to_string(val); };

#include <cstring>