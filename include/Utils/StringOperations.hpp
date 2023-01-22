
#pragma once

#include <string>
#include <vector>

using StringVector = std::vector<std::string>;

class StringOperations {
public:
    static StringVector split(std::string const& str, char delimiter);
    static std::string strip(std::string const& str);
};