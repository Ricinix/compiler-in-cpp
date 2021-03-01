//
// Created by laugh on 2020/12/31.
//

#ifndef DESIGN_1_PARSER_H
#define DESIGN_1_PARSER_H

#include "../rule/RuleSet.h"
#include "../lexer/Lexer.h"
#include "ParseTree.h"

class Parser {
private:
    RuleSet* rules;
    Lexer* mLexer;
    ParseTree* parseTree;
    Token* nowToken = nullptr;
    bool hasGetParseTree;

    void parseFromTop();
    /**
     * 递归地构造子树
     * @return 构造子树是否成功
     */
    bool recurParseFromTop(ParseTreeNode* node);

    Token *getNowToken();
    void nextToken();
public:
    Parser(RuleSet* ruleSet, Lexer* lexer);
    ~Parser();
    ParseTree* getParseTree();
    void parse();
};


#endif //DESIGN_1_PARSER_H
