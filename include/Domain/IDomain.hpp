
#pragma once

#include "Torrent.hpp"

class IDomain {
public:
    virtual ~IDomain() = default;

public:
    virtual Torrent addTorrentViaMagnetLink(std::string const& magnetLink) = 0;
    virtual Torrent deleteTorrentById(std::string const& id) = 0;
    virtual Torrents getTorrents() = 0;
};