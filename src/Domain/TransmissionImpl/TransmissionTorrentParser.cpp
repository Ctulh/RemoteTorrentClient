//
// Created by ctuh on 1/20/23.
//
#include "Domain/TransmissionImpl/TransmissionTorrentParser.hpp"
#include "Utils/StringOperations.hpp"
#include "Domain/TorrentBuilder.hpp"

#include <numeric>
#include <assert.h>
#include <ranges>
#include <algorithm>
#include <regex>

namespace {
    std::regex idRegex(R"(\s*\d+\S*)");
    std::regex percentsDownloadedRegex(R"(\s+\d*\%|n\/a)");
    std::regex downloadSizeRegex(R"(\s*\d+\.{1}\d+\s+\w{2}\s+|\s+None\s+)");
    std::regex timeLeftRegex(R"(\s+\d+\s+\w+\s+|\s+Unknown\s+|\s+Done\s+)");
    std::regex uploadSpeedRegex(R"(\s+\d+\.\d+\s+\W)");
    std::regex downloadSpeedRegex(R"(\d\s+\d+.\d+\s+)");
    std::regex ratioRegex(R"(\s+\d+.\d+\s+Idle|\s+\d+.\d+\s+Downloading)");
    std::regex downloadStatusRegex(R"(\s+Idle|\s+Downloading)");
    std::regex torrentNameRegex(R"(Idle\s+.+|Downloading\s+.+|Stopped\s+.+)");

    std::string getTorrentId(std::string const& data) {
        std::smatch match;
        if(std::regex_search(data, match, idRegex)) {
            return StringOperations::strip(match[0]);
        }
        return "IdNotFound";
    }

    std::string getDownloadedPercents(std::string const& data) {
        std::smatch match;
        if(std::regex_search(data, match, percentsDownloadedRegex)) {
            return StringOperations::strip(match[0]);
        }
        return "PercentsNotFound";
    }

    std::string getDownloadSize(std::string const& data) {
        std::smatch match;
        if(std::regex_search(data, match, downloadSizeRegex)) {
            return StringOperations::strip(match[0]);
        }
        return "DownloadedSizeNotFound";
    }

    std::string getTimeLeft(std::string const& data) {
        std::smatch match;
        if(std::regex_search(data, match, timeLeftRegex)) {
            return StringOperations::strip(match[0]);
        }
        return "TimeLeftNotFound";
    }

    std::string getUploadSpeed(std::string const& data) {
        std::smatch match;
        if(std::regex_search(data, match, uploadSpeedRegex)) {
            return StringOperations::strip(match[0]);
        }
        return "UploadSpeedNotFound";
    }

    std::string getDownloadSpeed(std::string const& data) {
        std::smatch match;
        if(std::regex_search(data, match, downloadSpeedRegex)) {
            auto downloadString = match[0].str().substr(1); // Because regex select last digit of from upload speed
            return StringOperations::strip(downloadString);
        }
        return "DownloadSpeedNotFound";
    }

    std::string getTorrentName(std::string const& data) {
        std::smatch match;
        if(std::regex_search(data, match, torrentNameRegex)) {
            auto matchString = match[0].str();
            auto beginOfTheTorrentName = matchString.find(' '); // Because regex select download status with torrent name and this fields separated by space symbol, so after first space only the name of the torrent remains in the string
            auto torrentName = matchString.substr(beginOfTheTorrentName);

            return StringOperations::strip(torrentName);
        }
        return "TorrentNameNotFound";
    }

}

std::vector<Torrent> TransmissionTorrentParser::stringToTorrents(const std::string &data) {
    std::vector<Torrent> result;

    auto lines = StringOperations::split(data, '\n');

    if(lines.size() <= 1)
        return result;

    auto parseLineToTorrent = [&result](auto line) {
        auto elements = StringOperations::split(line, ' ');

        if(elements.size() < 9)
            return;

        std::string torrentName;
        std::ranges::for_each(elements.begin() + 8, elements.end(), [&torrentName](auto partOfName) {torrentName += partOfName + " ";});
        torrentName.erase(torrentName.end()-1);

        auto torrent = TorrentBuilder()
                        .withId(::getTorrentId(line))
                        .withPercentsDone(::getDownloadedPercents(line))
                        .withDownloaded(::getDownloadSize(line))
                        .withTimeLeft(::getTimeLeft(line))
                        .withUploadSpeed(::getUploadSpeed(line))
                        .withDownloadSpeed(::getDownloadSpeed(line))
                        .withName(::getTorrentName(line))
                        .build();

        result.push_back(torrent);
    };

    std::ranges::for_each(lines.begin() + 1, lines.end() - 1, parseLineToTorrent);
    return result;
}