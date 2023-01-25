//
// Created by ctuh on 1/25/23.
//

#include "Utils/FileReader.hpp"

#include <fstream>

std::string FileReader::getData(const std::string &filePath) {
    std::ifstream t(filePath);
    std::string data((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    return data;
}
