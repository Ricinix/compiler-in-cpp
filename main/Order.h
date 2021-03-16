//
// Created by laugh on 2020/12/17.
//

#ifndef DESIGN_1_ORDER_H
#define DESIGN_1_ORDER_H

#include <string>
#include "../parser/Parser.h"

enum class OrderType {
    ERROR,
    COMPILE
};

class Order {
public:
    Order(std::string &src, std::string &target, OrderType type);

    Order();

    OrderType getOrderType();

    virtual void exec();

private:
    std::string srcPath;
    std::string targetPath;
    OrderType orderType;
protected:
    std::string getSrcPath();

    std::string getTargetPath();
};

class CompileOrder : public Order {
private:
    static AbstractSyntaxTree *getAst(const std::string &inPath);
    void generateExe(IoUtil &ioUtil);
public:
    CompileOrder(std::string &src, std::string &target, OrderType type);

    void exec() override;
};


#endif //DESIGN_1_ORDER_H
