
#pragma once

#include "Framework/Interface.hpp"
#include "Application/IApplication.hpp"

#include <tgbot/tgbot.h>
#include <memory>
#include <atomic>

class TgAdapter: public Interface {
public:
    explicit TgAdapter(std::string const& configPath, std::shared_ptr<IApplication> application);
public:
    std::string addTorrent(std::string const& magnetUrl);
    std::string deleteTorrent(std::string const& torrentId);
    std::string getTorrents() const;
    void run();
    void stop();

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
