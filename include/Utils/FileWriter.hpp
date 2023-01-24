
#pragma once

#include <string>

class FileWriter {
public:
    static bool write(std::string const& data, std::string const& filePath);
};