//
// Created by ctuh on 1/20/23.
//

#include "Domain/TransmissionImpl/TransmissionTorrentClient.hpp"
#include "Domain/TransmissionImpl/TransmissionTorrentPerformer.hpp"
#include "Domain/TransmissionImpl/TransmissionTorrentParser.hpp"
#include "Domain/TorrentBuilder.hpp"

TransmissionTorrentClient::TransmissionTorrentClient() {
    TransmissionTorrentPerformer::init();
}

Torrent TransmissionTorrentClient::addTorrent(std::string const& url) {
    auto addResult = TransmissionTorrentPerformer::addTorrent(url);
    if(addResult) {
        return TorrentBuilder().withMessage("Success").build();
    }
    return TorrentBuilder().withMessage("Error").build();
}

Torrent TransmissionTorrentClient::deleteTorrent(std::string const& id) {
    auto deleteResult = TransmissionTorrentPerformer::deleteTorrent(id);
    if(deleteResult.find("success") != std::string::npos) {
        return TorrentBuilder().withMessage("Success").build();
    }
    return TorrentBuilder().withMessage("Error").build();
}

Torrents TransmissionTorrentClient::getTorrents() const {
    auto torrents = TransmissionTorrentPerformer::getTorrents();
    return TransmissionTorrentParser::stringToTorrents(torrents);
}