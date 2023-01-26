//
// Created by ctuh on 1/19/23.
//
#include <tgbot/tgbot.h>

#include "Framework/Adapters/TgAdapter.hpp"
#include "Utils/FileWriter.hpp"
#include "Utils/JsonConfigReader.hpp"
#include "Utils/WrongConfigPathException.hpp"

namespace {
    std::string addCommandString = "/add";

    std::atomic<bool> volatile hasSignalValue = false;

    void handleSignal(int) {
        hasSignalValue = true;
    }
}

TgAdapter::TgAdapter(std::string const& configPath, std::shared_ptr<IApplication> application): m_application(std::move(application)) {

    signal(SIGINT, ::handleSignal);

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
        auto torrentName = shortTheLine(torrent.name);
        auto torrentId = torrent.id;
        if(torrentId.back() == '*')
            torrentId = torrentId.substr(0, torrentId.size()-1);

        resultMessage << torrentId << ". " << std::string(torrentName.begin(), torrentName.end()) << " ";
        resultMessage << downloadedPercentsToLoadBar(torrent.percentsDone);

        if(torrent.timeLeft != "Done") {
            resultMessage << std::fixed << std::setprecision(2);
            resultMessage << " " << toMegabytesInSecond(torrent.downloadSpeed)<< " MB/s";
        }
        resultMessage << std::endl;
    };

    std::ranges::for_each(torrents->begin(), torrents->end(), writeTorrentInfo);
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

std::wstring TgAdapter::getSpaces(int amount) {
    std::wstring outputString;
    for(int i = 0; i < amount; i++)
        outputString += ' ';
    return outputString;
}

std::wstring TgAdapter::shortTheLine(std::string const& inputString, int outputLength) {
    if(inputString.size() <= outputLength) {
        std::wstring outputString(inputString.begin(), inputString.end());
        outputString += getSpaces(outputLength - inputString.length() + 1);
        return outputString;
    }

    std::wstring const endOfShortedString = L"...";
    std::wstring outputString;

    std::for_each(inputString.begin(), inputString.end(), [&outputString, outputLength, endOfShortedString](auto symbol) {
        if(outputString.length() <= outputLength - endOfShortedString.length())
            if(std::isdigit(symbol) || std::isalpha(symbol) || symbol == ' ')
                outputString.push_back(symbol);
    });
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
    TgBot::TgLongPoll longPoll(*m_bot);
    while (not ::hasSignalValue) {
        longPoll.start();
    }
}

void TgAdapter::stop() {
    ::hasSignalValue = false;
}
