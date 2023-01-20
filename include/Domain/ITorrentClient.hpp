
#pragma once

#include <string>
#include "Torrent.hpp"

class ITorrentClient {
public:
    virtual ~ITorrentClient() = default;
public:
    virtual Torrent addTorrent(std::string const& url) = 0;
    virtual Torrent deleteTorrent(std::string const& id) = 0;
    virtual Torrents getTorrents() const = 0;
};