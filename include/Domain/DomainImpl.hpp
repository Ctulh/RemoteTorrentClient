
#pragma once

#include "TorrentBuilder.hpp"
#include "IDomain.hpp"
#include "ITorrentClient.hpp"

#include <concepts>
#include <memory>

template <typename T>
concept TorrentClientBase = std::is_base_of_v<ITorrentClient, T> && std::is_default_constructible_v<T>;

template<TorrentClientBase TorrentClientType>
class DomainImpl: public IDomain {
public:
    DomainImpl(std::string const& configPath);
public:
    Torrent addTorrentViaMagnetLink(const std::string &magnetLink) override;
    Torrent deleteTorrentById(std::string const& id) override;
    Torrents getTorrents() override;
private:
    std::unique_ptr<ITorrentClient> m_torrentClient;
};

template<TorrentClientBase TorrentClientType>
DomainImpl<TorrentClientType>::DomainImpl(const std::string &configPath) {
    m_torrentClient = std::make_unique<TorrentClientType>();
}

template<TorrentClientBase TorrentClientType>
Torrent DomainImpl<TorrentClientType>::addTorrentViaMagnetLink(const std::string &magnetLink) {
    return m_torrentClient->addTorrent(magnetLink);
}

template<TorrentClientBase TorrentClientType>
Torrent DomainImpl<TorrentClientType>::deleteTorrentById(std::string const& id) {
    return m_torrentClient->deleteTorrent(id);
}

template<TorrentClientBase TorrentClientType>
Torrents DomainImpl<TorrentClientType>::getTorrents() {
    return m_torrentClient->getTorrents();
}

