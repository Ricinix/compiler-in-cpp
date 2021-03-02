//
// Created by laugh on 2021/3/1.
//

#ifndef DESIGN_1_RULEITEM_H
#define DESIGN_1_RULEITEM_H

#include <string>
#include "../domain/constant.h"
#include "../lexer/Token.h"

/**
 * 文法项的抽象类
 */
class RuleItem {
protected:
    std::string symbolName;
public:
    explicit RuleItem(const std::string &name);
    std::string getSymbolName();
    virtual bool isTerminal();
    virtual bool matchToken(Token* token);
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
    bool isTerminal() override;
    bool matchToken(Token *token) override;
};

/**
 * 非终结符
 */
class NonTerminalSymbol : public RuleItem {
public:
    explicit NonTerminalSymbol(const std::string &name);
    bool isTerminal() override;
    bool matchToken(Token *token) override;
};

/**
 * ε
 */
class EmptySymbol : public RuleItem {

public:
    explicit EmptySymbol();
    bool isTerminal() override;
    bool matchToken(Token *token) override;
};



#endif //DESIGN_1_RULEITEM_H