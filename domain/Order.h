//
// Created by laugh on 2020/12/17.
//

#ifndef DESIGN_1_ORDER_H
#define DESIGN_1_ORDER_H

#include <string>

enum class OrderType {
    ERROR,
    COMPILE
};

class Order {
public:
    Order(std::string &src, std::string &target, OrderType type);
    Order();
    std::string getSrcPath();
    std::string getTargetPath();
    OrderType getOrderType();

private:
    std::string srcPath;
    std::string targetPath;
    OrderType orderType;
};


#endif //DESIGN_1_ORDER_H
