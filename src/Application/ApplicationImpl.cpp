//
// Created by ctuh on 1/19/23.
//
#include "Application/ApplicationImpl.hpp"
#include <ranges>

Torrent ApplicationImpl::addTorrent(std::string const& torrent) {
    auto result = m_domain->addTorrentViaMagnetLink(torrent);
    return result;
}

Torrent ApplicationImpl::deleteTorrent(std::string const& torrentId) {
    return m_domain->deleteTorrentById(torrentId);
}

std::optional<Torrent> ApplicationImpl::getTorrent(std::string const& torrentId) const {
    auto torrents = m_domain->getTorrents();
    auto torrent = std::ranges::find_if(torrents.begin(), torrents.end(), [torrentId](auto torrent){return torrentId == torrent.id;});
    if(torrent == torrents.end()) {
        Torrent notFoundedTorrent;
        notFoundedTorrent.message = "Torrent with id: " + torrentId + " doesn't exist";
        return notFoundedTorrent;
    }
    return *torrent;
}

std::optional<Torrents> ApplicationImpl::getTorrents() const {
    return m_domain->getTorrents();
}