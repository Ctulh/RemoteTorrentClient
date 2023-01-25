
#pragma once

#include <string>

class TransmissionTorrentPerformer {
public:
    TransmissionTorrentPerformer() = delete;
public:
    static bool init();
    static bool setDestinationPath(std::string const& destinationPath);
    static bool addTorrent(std::string const& torrent);
    static std::string deleteTorrent(std::string const& torrentId);
    static std::string getTorrents();
};
