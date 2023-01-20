//
// Created by ctuh on 1/20/23.
//
#include "Domain/TransmissionImpl/TransmissionTorrentParser.hpp"
#include "Utils/StringOperations.hpp"
#include "Domain/TorrentBuilder.hpp"

#include <numeric>
#include <ranges>
#include <algorithm>

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
                        .withId(elements[0])
                        .withPercentsDone(elements[1])
                        .withDownloaded(elements[2])
                        .withTimeLeft(elements[3])
                        .withUploadSpeed(elements[4])
                        .withDownloadSpeed(elements[5])
                        .withName(torrentName)
                        .build();

        result.push_back(torrent);
    };

    std::ranges::for_each(lines.begin() + 1, lines.end() - 1, parseLineToTorrent);
    return result;
}