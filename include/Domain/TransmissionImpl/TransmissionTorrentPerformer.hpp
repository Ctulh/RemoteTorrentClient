
#pragma once

#include <string>

class TransmissionTorrentPerformer {
public:
    TransmissionTorrentPerformer() = delete;
public:
    static bool init();
    static bool addTorrent(std::string const& data);
    static std::string deleteTorrent(std::string const& id);
    static std::string getTorrents();
};
