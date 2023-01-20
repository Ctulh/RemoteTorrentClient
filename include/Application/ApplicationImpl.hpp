
#pragma once

#include "IApplication.hpp"
#include "Domain/IDomain.hpp"

#include <memory>

class ApplicationImpl: public IApplication {
public:
    ApplicationImpl(std::unique_ptr<IDomain> domain): m_domain(std::move(domain)) {}
public:
    Torrent addTorrent(std::string const&) override;
    std::optional<Torrent> getTorrent(std::string const& number) const override;
    std::optional<Torrents> getTorrents() const override;
    Torrent deleteTorrent(std::string const& number) override;

private:
    std::unique_ptr<IDomain> m_domain;
};
