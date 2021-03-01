//
// Created by laugh on 2021/3/1.
//

#ifndef DESIGN_1_RULEITEM_H
#define DESIGN_1_RULEITEM_H

#include <string>
#include "../domain/constant.h"

/**
 * 文法项的抽象类
 */
class RuleItem {
protected:
    std::string symbolName;
public:
    explicit RuleItem(const std::string &name);
};

/**
 * 终结符
 */
class TerminalSymbol : public RuleItem {
private:
    TokenType tokenType;
public:
    explicit TerminalSymbol(const std::string &name);
    explicit TerminalSymbol(TokenType type);
};

/**
 * 非终结符
 */
class NonTerminalSymbol : public RuleItem {
public:
    explicit NonTerminalSymbol(const std::string &name);
};

/**
 * ε
 */
class EmptySymbol : public RuleItem {

public:
    explicit EmptySymbol();
};



#endif //DESIGN_1_RULEITEM_H
