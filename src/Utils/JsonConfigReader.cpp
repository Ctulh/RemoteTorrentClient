//
// Created by ctuh on 1/25/23.
//

#include "Utils/JsonConfigReader.hpp"
#include "Utils/WrongConfigPathException.hpp"

#include <nlohmann/json.hpp>
#include <fstream>

using namespace nlohmann;

struct JsonConfigReader::Impl {
    json data;
};

JsonConfigReader::~JsonConfigReader() = default;

JsonConfigReader::JsonConfigReader(std::string const& configPath): m_configPath(configPath) {
    try {
        std::ifstream config(m_configPath);
        m_jsonData = std::make_unique<Impl>();
        m_jsonData->data = json::parse(config);
    }
    catch (std::exception& e) {
        throw WrongConfigPathException("Can't read config: " + configPath);
    }
}

std::optional<std::string> JsonConfigReader::operator[](std::string const& field) const {
    try {
        return m_jsonData->data[field.c_str()];
    }
    catch(std::exception& e) {
        return {};
    }
}