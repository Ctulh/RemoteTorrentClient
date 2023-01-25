
#pragma once

#include <string>
#include "Torrent.hpp"

class ITorrentClient {
public:
    virtual ~ITorrentClient() = default;
public:
    virtual void setDownloadDestination(std::string const& downloadDirectory) = 0;
    virtual Torrent addTorrent(std::string const& torrent) = 0;
    virtual Torrent deleteTorrent(std::string const& id) = 0;
    virtual Torrents getTorrents() const = 0;
};