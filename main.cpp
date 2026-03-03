#include <iostream>
#include <vector>

#include <boost/program_options.hpp>

#include "bmp.hpp"
#include "bmp_factory.hpp"

namespace po = boost::program_options;

namespace {
    constexpr std::string_view kProgramName = "image-processor";
}

int main(int argc, char** argv) {
    po::options_description desc(::kProgramName.data());
    desc.add_options()
        ("help", "show help message")
        ("show-work", po::value<bool>()->default_value(false), "show factory usage");
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help") || argc == 1) {
        std::cout << desc << std::endl;
        return 0;
    }

    if (vm["show-work"].as<bool>()) {
        std::vector<std::unique_ptr<bmp::BmpFactory>> factories;
    
        factories.push_back(std::make_unique<bmp::BmpFromCLIFactory>(123));
        factories.push_back(std::make_unique<bmp::BmpFromFile>("/some/path"));
    
        for (const auto& factory : factories)
            auto f = factory->CreatePicture();
    }

    return 0;
}
