
#pragma once

#include <string>
#include <optional>
#include <vector>

#include "Domain/Torrent.hpp"

class IApplication {
public:
    virtual ~IApplication() = default;

public:
    virtual Torrent addTorrent(std::string const&) = 0;
    virtual std::optional<Torrent> getTorrent(std::string const& number) const = 0;
    virtual std::optional<Torrents> getTorrents() const = 0;
    virtual Torrent deleteTorrent(std::string const& number) = 0;
};
