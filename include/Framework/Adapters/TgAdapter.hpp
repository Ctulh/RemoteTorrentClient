
#pragma once

#include "Framework/Interface.hpp"
#include "Application/IApplication.hpp"

#include <tgbot/tgbot.h>
#include <memory>
#include <atomic>

class TgAdapter final : public Interface {
public:
    explicit TgAdapter(std::string const& configPath, std::shared_ptr<IApplication> application);
public:
    std::string addTorrent(std::string const& torrent) override;
    std::string deleteTorrent(std::string const& torrentId) override;
    std::string getTorrents() const override;
    void run();
    void stop();

private:
    std::string addTorrentImpl(std::string const& torrent);
    std::string deleteTorrentImpl(std::string const& torrentId);
    std::string onFileSentImpl(std::string const& fileId, std::string const& fileName);
private:
    static double toMegabytesInSecond(std::string const& speed);
    static std::string downloadedPercentsToLoadBar(std::string const& downloaded);
    static std::string shortTheLine(std::string const& inputString, int outputLength = 30);

private:
    std::atomic_flag m_isRunning;
    std::string m_token;
    TgBot::Bot m_bot;
    std::shared_ptr<IApplication> m_application;
};
