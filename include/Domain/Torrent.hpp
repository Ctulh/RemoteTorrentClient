
#pragma once

#include <string>
#include <vector>
#include <optional>

using IdType = uint32_t;

struct Torrent {
    std::optional<std::string> message;
    std::string id;
    std::string downloaded;
    std::string name;
    std::string downloadSpeed;
    std::string uploadSpeed;
    std::string done;
    std::string timeLeft;
};

using Torrents = std::vector<Torrent>;
