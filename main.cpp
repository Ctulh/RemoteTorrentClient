#include <iostream>
#include <boost/program_options.hpp>

#include "include/Domain/DomainImpl.hpp"
#include "include/Application/ApplicationImpl.hpp"
#include "Framework/IAdapter.hpp"
#include "Framework/Adapters/TgAdapter.hpp"
#include "Domain/TransmissionImpl/TransmissionTorrentClient.hpp"

namespace po = boost::program_options;

int main(int argc, char** argv) {

    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("config", po::value<std::string>(), "config path")
            ("tgconfig", po::value<std::string>(), "telegram config path");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if(vm.count("help")) {
        std::cout << desc << '\n';
        return 1;
    }

    std::string configPath;
    std::string telegramConfigPath;

    if(vm.count("config")) {
        std::cout << "config: " << vm["config"].as<std::string>() << '\n';
        configPath = vm["config"].as<std::string>();
    }

    if(vm.count("tgconfig")) {
        std::cout << "tgconfig: " << vm["tgconfig"].as<std::string>() << '\n';
        telegramConfigPath = vm["tgconfig"].as<std::string>();
    }

    if(configPath.empty()) {
        std::cout << "no config path";
        return 1;
    }

    if(telegramConfigPath.empty()) {
        std::cout << "no telegram config path";
        return 1;
    }

    std::unique_ptr<IDomain> domain;
    std::shared_ptr<IApplication> application;
    std::unique_ptr<IAdapter> adapter;

    try {
        domain = std::make_unique<DomainImpl<TransmissionTorrentClient>>(configPath);
        application = std::make_shared<ApplicationImpl>(std::move(domain));
        adapter = std::make_unique<TgAdapter>(telegramConfigPath, application);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    adapter->run();

    return 0;
}
