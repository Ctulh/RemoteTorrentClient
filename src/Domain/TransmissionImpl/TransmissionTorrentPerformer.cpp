//
// Created by ctuh on 1/20/23.
//
#include "Domain/TransmissionImpl/TransmissionTorrentPerformer.hpp"

#include <stdio.h>
#include <iostream>

bool TransmissionTorrentPerformer::init() {
    std::string resultString;
    FILE *fp = popen("transmission-daemon", "r");
    char buf[1024];

    while (fgets(buf, 1024, fp)) {
        resultString += buf;
    }
    if(resultString.empty())
        return true;
    return false;
}

bool TransmissionTorrentPerformer::addTorrent(const std::string &magnetLink) {
    std::string resultString;
    FILE *fp = popen( ("transmission-remote -a \"" + magnetLink + '\"').c_str(), "r");
    char buf[1024];

    while (fgets(buf, 1024, fp)) {
        resultString += buf;
    }
    if(resultString.find("Error") != std::string::npos)
        return false;
    return true;
}

std::string TransmissionTorrentPerformer::deleteTorrent(std::string const& id) {
    std::string resultString;
    FILE *fp = popen( ("transmission-remote -t " + id + " -r").c_str(), "r");
    char buf[1024];

    while (fgets(buf, 1024, fp)) {
        resultString += buf;
    }
    return resultString;
}

std::string TransmissionTorrentPerformer::getTorrents() {
    std::string resultString;
    FILE *fp = popen("transmission-remote -l", "r");
    char buf[1024];

    while (fgets(buf, 1024, fp)) {
        resultString += buf;
    }
    return resultString;
}