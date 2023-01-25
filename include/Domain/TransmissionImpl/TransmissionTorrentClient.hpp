
#pragma once

#include "Domain/ITorrentClient.hpp"

class TransmissionTorrentClient final: public ITorrentClient {
public:
    TransmissionTorrentClient(std::string const& configPath);
public:
    void setDownloadDestination(const std::string &downloadDirectory) override;
    Torrent addTorrent(std::string const& torrent) override;
    Torrent deleteTorrent(std::string const& torrentId) override;
    Torrents getTorrents() const override;
};