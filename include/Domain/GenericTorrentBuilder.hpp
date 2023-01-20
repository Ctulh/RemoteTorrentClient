
#pragma once

#include <string>
#include "Torrent.hpp"

template <typename ConcreteBuilder>
class GenericTorrentBuilder {
public:
    GenericTorrentBuilder() = default;
    virtual ~GenericTorrentBuilder() = default;
public:
    Torrent && build() {
        return std::move(m_torrent);
    }

    ConcreteBuilder&& withDownloaded(std::string const& downloaded) {
        m_torrent.downloaded = downloaded;
        return static_cast<ConcreteBuilder&&>(*this);
    }

    ConcreteBuilder&& withId(std::string const& id) {
        m_torrent.id = id;
        return static_cast<ConcreteBuilder&&>(*this);
    }
    ConcreteBuilder&& withName(std::string const& name) {
        m_torrent.name = name;
        return static_cast<ConcreteBuilder&&>(*this);
    }
    ConcreteBuilder&& withDownloadSpeed(std::string const& downloadSpeed) {
        m_torrent.downloadSpeed = downloadSpeed;
        return static_cast<ConcreteBuilder&&>(*this);
    }
    ConcreteBuilder&& withUploadSpeed(std::string const& uploadSpeed) {
        m_torrent.uploadSpeed = uploadSpeed;
        return static_cast<ConcreteBuilder&&>(*this);
    }
    ConcreteBuilder&& withTimeLeft(std::string const& timeLeft) {
        m_torrent.timeLeft = timeLeft;
        return static_cast<ConcreteBuilder&&>(*this);
    }
    ConcreteBuilder&& withPercentsDone(std::string const& percentsDone) {
        m_torrent.done = percentsDone;
        return static_cast<ConcreteBuilder&&>(*this);
    }

protected:
    Torrent m_torrent;
};
