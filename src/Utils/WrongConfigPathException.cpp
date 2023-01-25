//
// Created by ctuh on 1/25/23.
//
#include "Utils/WrongConfigPathException.hpp"

WrongConfigPathException::WrongConfigPathException(const std::string &message) : m_message(message) {}

const char *WrongConfigPathException::what() const noexcept {
    return m_message.c_str();
}
