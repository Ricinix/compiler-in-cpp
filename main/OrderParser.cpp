//
// Created by laugh on 2020/12/17.
//

#include "OrderParser.h"
#include <algorithm>

std::unique_ptr<Order> OrderParser::parse(int argc, char *argv[]) {
    if (argc < 3) {
        return std::make_unique<Order>();
    }
    std::string instruction = argv[1];
    std::string srcPath = _parsePath(argv[0], argv[2]);
    std::string targetPath = argc < 4 ? std::string("") : _parsePath(argv[0], argv[3]);
    if (instruction == "-c") {
        return std::make_unique<CompileOrder>(srcPath, targetPath, OrderType::COMPILE);
    }
    return std::make_unique<Order>();
}

std::string OrderParser::_parsePath(const char *programPath, const char *filePath) {
    std::string origin = programPath;
    std::string target;
    int num = std::count(origin.cbegin(), origin.cend(), '\\');
    while (num-- > 0) {
        target += "..\\";
    }
    target += filePath;
    return target;
}
