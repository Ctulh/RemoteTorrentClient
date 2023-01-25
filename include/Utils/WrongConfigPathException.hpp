
#pragma once

#include <exception>
#include <string>

class WrongConfigPathException: public std::exception {
public:
    WrongConfigPathException(std::string const& message);

public:
    const char * what() const noexcept override;

private:
    std::string m_message;
};
