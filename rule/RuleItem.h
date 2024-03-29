//
// Created by laugh on 2021/3/1.
//

#ifndef DESIGN_1_RULEITEM_H
#define DESIGN_1_RULEITEM_H

#include <string>
#include "../domain/constant.h"
#include "../lexer/Token.h"

enum class RuleItemType {
    NonTerminal,
    Terminal,
    Empty,
    End, // 给follow集用的
};

/**
 * 文法项的抽象类
 */
class RuleItem {
protected:
    std::string symbolName;
public:
    explicit RuleItem(const std::string &name);
    virtual const std::string &getSymbolName();
    virtual RuleItemType getRuleItemType();
    virtual bool matchToken(Token* token);
};

/**
 * 终结符
 */
class TerminalSymbol : public RuleItem {
private:
    TokenType tokenType;
    std::string terminalName;
public:
    explicit TerminalSymbol(const std::string &name);
    explicit TerminalSymbol(TokenType type);
    RuleItemType getRuleItemType() override;
    bool matchToken(Token *token) override;
    const std::string &getSymbolName() override;
};

/**
 * 非终结符
 */
class NonTerminalSymbol : public RuleItem {
public:
    explicit NonTerminalSymbol(const std::string &name);
    RuleItemType getRuleItemType() override;
    bool matchToken(Token *token) override;
};

/**
 * ε
 */
class EmptySymbol : public RuleItem {

public:
    explicit EmptySymbol();
    RuleItemType getRuleItemType() override;
    bool matchToken(Token *token) override;
};

class EndSymbol : public RuleItem {
public:
    explicit EndSymbol();
    RuleItemType getRuleItemType() override;
    bool matchToken(Token *token) override;
};



#endif //DESIGN_1_RULEITEM_H
