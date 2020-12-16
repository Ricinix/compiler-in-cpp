//
// Created by laugh on 2020/12/17.
//

#include "OrderParser.h"
#include <algorithm>

Order OrderParser::parse(int argc, char *argv[]) {
    if (argc < 4) {
        return Order();
    }
    std::string instruction = argv[1];
    std::string srcPath = _parsePath(argv[0], argv[2]);
    std::string targetPath = _parsePath(argv[0], argv[3]);
    if (instruction == "-c") {
        return Order(srcPath, targetPath, OrderType::COMPILE);
    }
    return Order();
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
