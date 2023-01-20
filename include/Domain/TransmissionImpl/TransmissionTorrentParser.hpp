
#pragma once

#include "Domain/Torrent.hpp"

class TransmissionTorrentParser {
public:
    static std::vector<Torrent> stringToTorrents(std::string const& data);
};
