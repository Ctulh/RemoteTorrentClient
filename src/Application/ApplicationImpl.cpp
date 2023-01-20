//
// Created by ctuh on 1/19/23.
//
#include "Application/ApplicationImpl.hpp"
#include <ranges>

Torrent ApplicationImpl::addTorrent(std::string const& magnetLink) {
    auto result = m_domain->addTorrentViaMagnetLink(magnetLink);
    return result;
}

Torrent ApplicationImpl::deleteTorrent(std::string const& number) {
    return m_domain->deleteTorrentById(number);
}

std::optional<Torrent> ApplicationImpl::getTorrent(std::string const& number) const {
    auto torrents = m_domain->getTorrents();
    auto torrent = std::ranges::find_if(torrents.begin(), torrents.end(), [number](auto torrent){return number == torrent.id;});
    if(torrent == torrents.end()) {
        Torrent notFoundedTorrent;
        notFoundedTorrent.message = "Torrent with id: " + number + " doesn't exist";
        return notFoundedTorrent;
    }
    return *torrent;
}

std::optional<Torrents> ApplicationImpl::getTorrents() const {
    return m_domain->getTorrents();
}