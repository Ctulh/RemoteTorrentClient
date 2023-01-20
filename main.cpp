#include <iostream>
#include <boost/program_options.hpp>

#include "include/Domain/DomainImpl.hpp"
#include "include/Application/ApplicationImpl.hpp"
#include "Framework/Adapters/TgAdapter.hpp"
#include "Domain/TransmissionImpl/TransmissionTorrentClient.hpp"

namespace po = boost::program_options;

int main(int argc, char** argv) {

    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("conf", po::value<std::string>(), "config path")
            ("tgconf", po::value<std::string>(), "telegram config path");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if(vm.count("help")) {
        std::cout << desc << '\n';
        return 1;
    }

    std::string configPath;
    std::string telegramConfigPath;

    if(vm.count("conf")) {
        std::cout << "conf: " << vm["conf"].as<std::string>() << '\n';
        configPath = vm["conf"].as<std::string>();
    }

    if(vm.count("tgconf")) {
        std::cout << "tgconf: " << vm["tgconf"].as<std::string>() << '\n';
        telegramConfigPath = vm["tgconf"].as<std::string>();
    }


    auto domain = std::make_unique<DomainImpl<TransmissionTorrentClient>>(configPath);
    auto application = std::make_shared<ApplicationImpl>(std::move(domain));
    auto adapter = std::make_shared<TgAdapter>("1", application);
    adapter->run();

    //if(not telegramConfigPath.empty())
    //    telegramConfigPath(application);

    return 0;
}
