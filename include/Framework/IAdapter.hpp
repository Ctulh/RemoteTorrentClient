
#pragma once

#include <string>
#include <optional>

#include "Domain/Torrent.hpp"

class IAdapter {
public:
    virtual ~IAdapter() = default;
public:
    virtual std::string addTorrent(std::string const& torrent) = 0;
    virtual std::string deleteTorrent(std::string const& torrentId) = 0;
    virtual std::string getTorrents() const = 0;

    virtual void run() = 0;
    virtual void stop() = 0;

};
