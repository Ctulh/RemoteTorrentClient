//
// Created by ctuh on 1/24/23.
//

#include "Utils/FileWriter.hpp"

#include <fstream>
#include <filesystem>


bool FileWriter::write(const std::string &data, const std::string &filePath) {
    auto endOfDirectoryPathPart = filePath.find_last_of('/');
    if(endOfDirectoryPathPart != std::string::npos) {
        std::string directoryPath = filePath.substr(0, endOfDirectoryPathPart);
        if (not std::filesystem::exists(directoryPath)) {
            std::filesystem::create_directories(directoryPath);
        }
    }

    std::ofstream out(filePath, std::ios::out | std::ios::binary);
    out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    out << data;
    out.close();
    return true;
}
