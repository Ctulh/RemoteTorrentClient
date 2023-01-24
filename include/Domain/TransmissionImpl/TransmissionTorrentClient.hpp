
#pragma once

#include "Domain/ITorrentClient.hpp"

class TransmissionTorrentClient final: public ITorrentClient {
public:
    TransmissionTorrentClient();
public:
    Torrent addTorrent(std::string const& url);
    Torrent deleteTorrent(std::string const& id);
    Torrents getTorrents() const;
};