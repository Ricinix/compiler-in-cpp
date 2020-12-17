//
// Created by laugh on 2020/12/17.
//

#include "Order.h"
#include "../util/Log.h"
#include "../lexer/Lexer.h"

Order::Order(std::string &src, std::string &target, OrderType type) {
    srcPath = src;
    targetPath = target;
    orderType = type;
}

std::string Order::getSrcPath() {
    return srcPath;
}

std::string Order::getTargetPath() {
    return targetPath;
}

OrderType Order::getOrderType() {
    return orderType;
}

Order::Order() {
    orderType = OrderType::ERROR;
}

void Order::exec() {
    Log::warm("do nothing");
}

CompileOrder::CompileOrder(std::string &src, std::string &target, OrderType type) : Order(src, target, type) {

}

void CompileOrder::exec() {
    IoUtil ioUtil(getSrcPath(), getTargetPath());
    Lexer lexer(ioUtil);
    Token *t_ptr = lexer.read();
    while (t_ptr != nullptr && t_ptr->getTokenType() != TokenType::eof) {
        Log::info(*t_ptr);
        t_ptr = lexer.read();
    }
}
