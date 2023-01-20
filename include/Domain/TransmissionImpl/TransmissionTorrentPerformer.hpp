
#pragma once

#include <string>

class TransmissionTorrentPerformer {
public:
    TransmissionTorrentPerformer() = delete;

public:
    static std::string addTorrent(std::string const& magnetLink);
    static std::string deleteTorrent(std::string const& id);
    static std::string getTorrents();
};
