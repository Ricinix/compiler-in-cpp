//
// Created by laugh on 2020/12/17.
//

#ifndef DESIGN_1_ORDERPARSER_H
#define DESIGN_1_ORDERPARSER_H

#include "Order.h"
#include <memory>

namespace OrderParser {
    std::unique_ptr<Order> parse(int argc, char *argv[]);
    std::string _parsePath(const char *programPath, const char* filePath);
}


#endif //DESIGN_1_ORDERPARSER_H
