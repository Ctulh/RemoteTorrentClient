//
// Created by ctuh on 1/20/23.
//

#include "Utils/StringOperations.hpp"

#include <algorithm>
#include <ranges>

std::string StringOperations::strip(std::string const& str) {
    std::input_iterator auto begin = std::ranges::find_if(str.begin(), str.end(), [](auto symbol) {
        return symbol != ' ';
    });

    std::input_iterator auto end = std::ranges::find_if(str.rbegin(), str.rend(), [](auto symbol) {
        return symbol != ' ';
    });

    return {begin, end.base()};
}

StringVector StringOperations::split(std::string const& str, char delimiter) {
    StringVector result;

    std::string buf;
    std::ranges::for_each(str.begin(), str.end(), [&result, &buf, delimiter](auto symbol) {
        if(symbol == delimiter) {
            if(!buf.empty()) {
                result.push_back(buf);
            }
            buf.clear();
            return;
        }
        buf += symbol;
    });
    if(not buf.empty())
        result.push_back(buf);

    return result;
}