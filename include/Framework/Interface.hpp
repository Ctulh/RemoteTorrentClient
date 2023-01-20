
#pragma once

#include <string>
#include <optional>

#include "Domain/Torrent.hpp"

class Interface {
public:
    virtual  ~Interface() = default;
public:
    virtual std::string addTorrent(std::string const& magnetUrl) = 0;
    virtual std::string deleteTorrent(std::string const& torrentId) = 0;
    virtual std::string getTorrents() const = 0;
};
