
#pragma once

#include "IApplication.hpp"
#include "Domain/IDomain.hpp"

#include <memory>

class ApplicationImpl: public IApplication {
public:
    ApplicationImpl(std::unique_ptr<IDomain> domain): m_domain(std::move(domain)) {}
public:
    Torrent addTorrent(std::string const& torrent) override;
    std::optional<Torrent> getTorrent(std::string const& torrentId) const override;
    std::optional<Torrents> getTorrents() const override;
    Torrent deleteTorrent(std::string const& torrentId) override;

private:
    std::unique_ptr<IDomain> m_domain;
};
