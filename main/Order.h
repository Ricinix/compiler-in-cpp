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
    Order(const std::string &src, const std::string &target, OrderType type);

    Order();

    OrderType getOrderType();

    virtual void exec();

private:
    std::string srcPath;
    std::string targetPath;
    OrderType orderType;
protected:
    const std::string &getSrcPath();

    const std::string &getTargetPath();
};

class CompileOrder : public Order {
private:
    static RuleSet *ruleSet;
    static StateTransitionTable *stateTransitionTable;

    static AbstractSyntaxTree *getAstByInPath(const std::string &inPath);

    static AbstractSyntaxTree *getAst(IoUtil &ioUtil);

    static void generateExe(IoUtil &ioUtil);

    static RuleSet *getRuleSet();

    static StateTransitionTable *getStateTable();

public:
    CompileOrder(const std::string &src, const std::string &target, OrderType type);

    void exec() override;
};


#endif //DESIGN_1_ORDER_H
