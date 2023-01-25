//
// Created by ctuh on 1/19/23.
//
#include <tgbot/tgbot.h>
#include <sstream>

#include "Framework/Adapters/TgAdapter.hpp"
#include "Utils/FileWriter.hpp"
#include "Utils/JsonConfigReader.hpp"
#include "Utils/WrongConfigPathException.hpp"

namespace {
    std::string addCommandString = "/add";
}


TgAdapter::TgAdapter(std::string const& configPath, std::shared_ptr<IApplication> application): m_application(std::move(application)) {
    auto configReader = JsonConfigReader(configPath);
    auto botApi = configReader["botApi"];
    auto chatFilesDownloadDestinationValue = configReader["chatFilesDownloadDestination"];

    if(!botApi.has_value()) {
        std::cerr << "can't find \"botApi\" field in config: " << configPath;
    }
    if(!chatFilesDownloadDestinationValue.has_value()) {
        std::cerr << "can't find \"chatFilesDownloadDestination\" field in config: " << configPath;
    }

    m_bot = std::make_unique<TgBot::Bot>(botApi.value());
    m_downloadDestination = chatFilesDownloadDestinationValue.value();


    m_bot->getEvents().onCommand("start", [this](TgBot::Message::Ptr message) {
        m_bot->getApi().sendMessage(message->chat->id, "Hi!");
    });

    m_bot->getEvents().onCommand("add", [this](TgBot::Message::Ptr message) {
        auto result = this->addTorrent(message->text);
        m_bot->getApi().sendMessage(message->chat->id, result);
    });

    m_bot->getEvents().onCommand("del", [this](TgBot::Message::Ptr message) {
        auto result = this->deleteTorrent(message->text);
        m_bot->getApi().sendMessage(message->chat->id, result);
    });

    m_bot->getEvents().onCommand("list", [this](TgBot::Message::Ptr message) {
        auto result = this->getTorrents();
        m_bot->getApi().sendMessage(message->chat->id, result);
    });

    m_bot->getEvents().onNonCommandMessage([this](TgBot::Message::Ptr message) {
        try {
            auto result = onFileSentImpl(message->document->fileId, message->document->fileName);
            m_bot->getApi().sendMessage(message->chat->id, result);
        }
        catch(std::exception& e) {
            m_bot->getApi().sendMessage(message->chat->id, "Cant process this message");
        }
    });
}

std::string TgAdapter::addTorrent(std::string const& torrent) {
    auto startPos = torrent.find(::addCommandString);
    if(startPos != std::string::npos) {
        startPos += ::addCommandString.size() + 1;
        return addTorrentImpl(torrent.substr(startPos));
    }
    return addTorrentImpl(torrent);
}

std::string TgAdapter::deleteTorrent(std::string const& message) {
    auto beginOfTorrentId = message.find(' ');
    if(beginOfTorrentId == std::string::npos)
        return "Error Id not found";

    auto torrentId = message.substr(beginOfTorrentId);

    return deleteTorrentImpl(torrentId);
}

std::string TgAdapter::getTorrents() const {
    auto torrents = m_application->getTorrents();
    std::stringstream resultMessage;

    auto writeTorrentInfo = [&resultMessage, this](auto torrent) {
        resultMessage << torrent.id << ". " << shortTheLine(torrent.name) << " ";
        resultMessage << downloadedPercentsToLoadBar(torrent.percentsDone);

        if(torrent.timeLeft != "Done") {
            resultMessage << std::fixed << std::setprecision(2);
            resultMessage << " " << toMegabytesInSecond(torrent.downloadSpeed) << " MB/s";
        }
        resultMessage << '\n';
    };

    std::ranges::for_each(torrents->begin(  ), torrents->end(), writeTorrentInfo);
    if(!resultMessage.str().empty())
        return resultMessage.str();
    return "No Torrents";
}

std::string TgAdapter::deleteTorrentImpl(std::string const& torrentId) {
    auto result = m_application->deleteTorrent(torrentId);
    if(result.message.has_value())
        return result.message.value();
    return "Error";
}

std::string TgAdapter::addTorrentImpl(const std::string &torrent) {
    auto result = m_application->addTorrent(torrent);
    if(result.message.has_value())
        return result.message.value();
    return "Unexpected result";
}

std::string TgAdapter::onFileSentImpl(std::string const& fileId, std::string const& fileName) {
    auto file = this->m_bot->getApi().getFile(fileId);
    auto fileData = this->m_bot->getApi().downloadFile(file->filePath);

    auto filePath = m_downloadDestination + fileName;
    FileWriter::write(fileData, filePath);

    return this->addTorrentImpl(filePath);
}

double TgAdapter::toMegabytesInSecond(const std::string &speed) {
    auto speedInKilobytesPerSecond = std::stod(speed);
    return speedInKilobytesPerSecond/1000.0;
}

std::string TgAdapter::shortTheLine(std::string const& inputString, int outputLength) {
    if(inputString.size() == outputLength)
        return inputString;

    std::string const endOfShortedString = "...";
    std::string outputString;

    outputString = inputString.substr(0, outputLength - endOfShortedString.size());
    outputString += endOfShortedString;
    return outputString;
}

std::string TgAdapter::downloadedPercentsToLoadBar(const std::string &downloaded) {
    const int symbolSize = 3; // Because ■ and □ increase string size by 3
    std::string result;
    int downloadedPercents;
    if (downloaded != "n/a")
        downloadedPercents = std::stoi(downloaded.substr(0, downloaded.size() - 1));
    else
        downloadedPercents = 0;

    assert(downloadedPercents <= 100);
    for(int i = 0; i < downloadedPercents / 10; i++) {
        result += "■";
    }
    while(result.length() < 10 * symbolSize) {
        result += "□";
    }
    return result;
}

void TgAdapter::run() {
    m_isRunning.test_and_set();
    TgBot::TgLongPoll longPoll(*m_bot);
    while (m_isRunning.test()) {
        longPoll.start();
    }
}

void TgAdapter::stop() {
    m_isRunning.clear();
}
