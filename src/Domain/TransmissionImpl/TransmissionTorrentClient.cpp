//
// Created by ctuh on 1/20/23.
//

#include "Domain/TransmissionImpl/TransmissionTorrentClient.hpp"
#include "Domain/TransmissionImpl/TransmissionTorrentPerformer.hpp"
#include "Domain/TransmissionImpl/TransmissionTorrentParser.hpp"
#include "Domain/TorrentBuilder.hpp"
#include "Utils/JsonConfigReader.hpp"

#include <iostream>

TransmissionTorrentClient::TransmissionTorrentClient(std::string const& configPath) {
    TransmissionTorrentPerformer::init();

    JsonConfigReader configReader(configPath);
    auto downloadDirectoryValue = configReader["downloadDirectory"];

    if(!downloadDirectoryValue.has_value()) {
        std::cerr << "can't find \"downloadDirectory\" field in config: " << configPath;
    }
    setDownloadDestination(downloadDirectoryValue.value());
}

void TransmissionTorrentClient::setDownloadDestination(const std::string &downloadDirectory) {
    TransmissionTorrentPerformer::setDestinationPath(downloadDirectory);
}

Torrent TransmissionTorrentClient::addTorrent(std::string const& torrent) {
    auto addResult = TransmissionTorrentPerformer::addTorrent(torrent);
    if(addResult) {
        return TorrentBuilder().withMessage("Success").build();
    }
    return TorrentBuilder().withMessage("Error").build();
}

Torrent TransmissionTorrentClient::deleteTorrent(std::string const& torrentId) {
    auto deleteResult = TransmissionTorrentPerformer::deleteTorrent(torrentId);
    if(deleteResult.find("success") != std::string::npos) {
        return TorrentBuilder().withMessage("Success").build();
    }
    return TorrentBuilder().withMessage("Error").build();
}

Torrents TransmissionTorrentClient::getTorrents() const {
    auto torrents = TransmissionTorrentPerformer::getTorrents();
    return TransmissionTorrentParser::stringToTorrents(torrents);
}