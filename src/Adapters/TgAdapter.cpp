//
// Created by ctuh on 1/19/23.
//
#include "Framework/Adapters/TgAdapter.hpp"
#include "tgbot/tgbot.h"

#include <sstream>

namespace {
    std::string addCommandString = "/add";
}


TgAdapter::TgAdapter(const std::string &configPath, std::shared_ptr<IApplication> application): m_application(std::move(application)),
                                                                                                m_bot("TokenHere") { //TODO config reader
    m_bot.getEvents().onCommand("start", [this](TgBot::Message::Ptr message) {
        m_bot.getApi().sendMessage(message->chat->id, "start");
    });

    m_bot.getEvents().onCommand("add", [this](TgBot::Message::Ptr message) {
        auto result = this->addTorrent(message->text);
        m_bot.getApi().sendMessage(message->chat->id, result);
    });
    m_bot.getEvents().onCommand("del", [this](TgBot::Message::Ptr message) {
        auto result = this->deleteTorrent(message->text);
        m_bot.getApi().sendMessage(message->chat->id, result);
    });
    m_bot.getEvents().onCommand("list", [this](TgBot::Message::Ptr message) {
        auto result = this->getTorrents();
        m_bot.getApi().sendMessage(message->chat->id, result);
    });
}

std::string TgAdapter::addTorrent(std::string const& message) {
    auto startPos = message.find(::addCommandString);
    if(startPos == std::string::npos) {
        return ("Wrong command: " + message);
    }
    startPos += ::addCommandString.size() + 1; // Because of space after command
    auto result = m_application->addTorrent(message.substr(startPos));

    std::stringstream ss;
    ss << "Torrent successfully added \n"
       << "Name: " << result.name << '\n'
       << "Id: " << result.id;

    return ss.str();
}
std::string TgAdapter::deleteTorrent(std::string const& torrentId) {
    return "Success";
}

std::string TgAdapter::getTorrents() const {
    auto torrents = m_application->getTorrents();
    std::stringstream resultMessage;

    auto writeTorrentInfo = [&resultMessage](auto torrent) {
        resultMessage << torrent.name << " " << torrent.downloaded << '\n';
    };

    std::ranges::for_each(torrents->begin(), torrents->end(), writeTorrentInfo);
    return resultMessage.str();
}

void TgAdapter::run() {
    TgBot::TgLongPoll longPoll(m_bot);
    while (true) {
        longPoll.start();
    }
}
