//
// Created by ctuh on 1/20/23.
//

#include "Utils/StringOperations.hpp"

#include <algorithm>
#include <ranges>

StringVector StringOperations::split(const std::string &str, char delimiter) {
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