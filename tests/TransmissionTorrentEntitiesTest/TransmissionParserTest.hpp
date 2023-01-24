
#pragma once

#include <gtest/gtest.h>
#include "Domain/TransmissionImpl/TransmissionTorrentParser.hpp"

TEST(TransmissionTorrentParser, test_transmission_string_parser_from_string) {
    std::string const stringForParse = "ID   Done       Have  ETA           Up    Down  Ratio  Status       Name\n"
                                       "     1    n/a       None  Unknown      0.0     0.0   None  Idle         (Pop Rock) [LP] [1/5.6] The Beatles – Let It Be - 2021, DSD 128 (tracks)\n"
                                       "Sum:                None               0.0     0.0";

    auto torrents = TransmissionTorrentParser::stringToTorrents(stringForParse);

    ASSERT_EQ(torrents.size(), 1);

    auto& torrentValue = torrents[0];

    ASSERT_EQ(torrentValue.id, "1");
    ASSERT_EQ(torrentValue.percentsDone, "n/a");
    ASSERT_EQ(torrentValue.downloaded, "None");
    ASSERT_EQ(torrentValue.timeLeft, "Unknown");
    ASSERT_EQ(torrentValue.uploadSpeed, "0.0");
    ASSERT_EQ(torrentValue.downloadSpeed, "0.0");
    ASSERT_EQ(torrentValue.name, "(Pop Rock) [LP] [1/5.6] The Beatles – Let It Be - 2021, DSD 128 (tracks)");
}

TEST(TransmissionTorrentParser, test_transmission_string_parser_from_string_with_more_than_one_torrents) {
    std::string const stringForParse = "ID   Done       Have  ETA           Up    Down  Ratio  Status       Name\n"
                                       "     1    n/a       None  Unknown      0.0     0.0   None  Idle         (Pop Rock) [LP] [1/5.6] The Beatles – Let It Be - 2021, DSD 128 (tracks)\n"
                                       "     2    n/a       None  Unknown      1.2     1.2   None  Idle         (Pop Rock) [LP] [1/5.6] The Beatles – Revolver - 2022, DSD 128 (tracks)\n"
                                       "Sum:                None               1.2     1.2";

    auto torrents = TransmissionTorrentParser::stringToTorrents(stringForParse);

    ASSERT_EQ(torrents.size(), 2);

    auto& torrentValue = torrents[0];

    ASSERT_EQ(torrentValue.id, "1");
    ASSERT_EQ(torrentValue.percentsDone, "n/a");
    ASSERT_EQ(torrentValue.downloaded, "None");
    ASSERT_EQ(torrentValue.timeLeft, "Unknown");
    ASSERT_EQ(torrentValue.uploadSpeed, "0.0");
    ASSERT_EQ(torrentValue.downloadSpeed, "0.0");
    ASSERT_EQ(torrentValue.name, "(Pop Rock) [LP] [1/5.6] The Beatles – Let It Be - 2021, DSD 128 (tracks)");

    torrentValue = torrents[1];

    ASSERT_EQ(torrentValue.id, "2");
    ASSERT_EQ(torrentValue.percentsDone, "n/a");
    ASSERT_EQ(torrentValue.downloaded, "None");
    ASSERT_EQ(torrentValue.timeLeft, "Unknown");
    ASSERT_EQ(torrentValue.uploadSpeed, "1.2");
    ASSERT_EQ(torrentValue.downloadSpeed, "1.2");
    ASSERT_EQ(torrentValue.name, "(Pop Rock) [LP] [1/5.6] The Beatles – Revolver - 2022, DSD 128 (tracks)");
}

TEST(TransmissionTorrentParser, test_transmission_string_parser_from_string_with_stopped_torrent) {
    std::string const stringForParse = " ID   Done       Have  ETA           Up    Down  Ratio  Status       Name\n"
                                       "     1*  100%   98.02 MB  Done         0.0     0.0    0.0  Stopped      Chip Z’Nuff - 2022 - Perfectly Imperfect\n"
                                       "Sum:            98.02 MB               0.0     0.0";

    auto torrents = TransmissionTorrentParser::stringToTorrents(stringForParse);

    ASSERT_EQ(torrents.size(), 1);

    auto& torrentValue = torrents[0];

    ASSERT_EQ(torrentValue.id, "1*");
    ASSERT_EQ(torrentValue.percentsDone, "100%");
    ASSERT_EQ(torrentValue.downloaded, "98.02 MB");
    ASSERT_EQ(torrentValue.timeLeft, "Done");
    ASSERT_EQ(torrentValue.uploadSpeed, "0.0");
    ASSERT_EQ(torrentValue.downloadSpeed, "0.0");
    ASSERT_EQ(torrentValue.name, "Chip Z’Nuff - 2022 - Perfectly Imperfect");
}


TEST(TransmissionTorrentParser, test_transmission_string_parser_from_string_without_torrent_data) {
    std::string const stringForParse = "ID   Done       Have  ETA           Up    Down  Ratio  Status       Name\n"
                                       "Sum:                None               0.0     0.0";

    auto torrents = TransmissionTorrentParser::stringToTorrents(stringForParse);

    ASSERT_EQ(torrents.size(), 0);
}
