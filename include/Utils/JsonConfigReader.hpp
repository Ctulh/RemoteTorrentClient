
#pragma once

#include <string>
#include <optional>
#include <memory>

class JsonConfigReader {
public:
    JsonConfigReader(std::string const& configPath) noexcept(false);
    ~JsonConfigReader();

public:
    std::optional<std::string> operator[](std::string const& field) const;

private:
    struct Impl;

private:
    std::string m_configPath;
    std::unique_ptr<Impl> m_jsonData;
};
