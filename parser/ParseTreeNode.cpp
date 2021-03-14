//
// Created by laugh on 2021/3/1.
//

#include "../domain/exception.h"
#include "ParseTreeNode.h"
#include "../ast/NumberLiteral.h"
#include "../ast/StringLiteral.h"
#include "../ast/Identifier.h"
#include "../ast/OpNodeProgram.h"
#include "../ast/OpNodeIf.h"
#include "../ast/OpNodeWhile.h"
#include "../ast/OpNodeBinaryExpr.h"
#include "../ast/OpNodeBlock.h"
#include "../ast/OpNodeSimple.h"
#include "../ast/OpNodeSingleExpr.h"
#include "../ast/DecorateNodePrimary.h"
#include "../ast/NewNodeArray.h"

ParseTreeNode::ParseTreeNode(RuleItem *ruleItem) {
    symbol = ruleItem;
    token = nullptr;
}

void ParseTreeNode::setFather(ParseTreeNode *node) {
    father = node;
}

ParseTreeNode *ParseTreeNode::getFather() {
    return father;
}

RuleItem *ParseTreeNode::getRuleItem() {
    return symbol;
}

ParseTreeNode::~ParseTreeNode() {
    for (auto &child : children) {
        delete child;
        child = nullptr;
    }
}

void ParseTreeNode::appendChild(ParseTreeNode *node) {
    node->setFather(this);
    children.push_back(node);
}

void ParseTreeNode::setChild(int pos, ParseTreeNode *node) {
    if (childNum() >= pos) {
        appendChild(node);
        return;
    }
    if (children[pos] != nullptr) {
        delete children[pos];
    }
    children[pos] = node;
    node->setFather(this);
}

ParseTreeNode *ParseTreeNode::getChild(int pos) {
    return children[pos];
}

int ParseTreeNode::childNum() {
    return children.size();
}

void ParseTreeNode::clearChildren() {
    children.clear();
}

bool ParseTreeNode::isLeaf() {
    return false;
}

ParseTreeNode::ParseTreeNode(RuleItem *ruleItem, Token *token_p) {
    symbol = ruleItem;
    token = token_p;
}

Token *ParseTreeNode::getToken() {
    return token;
}

std::string ParseTreeNode::getNodeName() const {
    return "";
}

ASTNode *ParseTreeNode::toASTNode() {
    return nullptr;
}

void ParseTreeNode::checkChildNum(int correctNum) {
    if (childNum() != correctNum) {
        throw ParseException(
                getNodeName() + " has wrong child num. correct: " + std::to_string(correctNum) + ", now: " +
                std::to_string(childNum()));
    }
}


ParseTreeLeaf::ParseTreeLeaf(RuleItem *ruleItem, Token *token_p) : ParseTreeNode(ruleItem, token_p) {

}

bool ParseTreeLeaf::isLeaf() {
    return true;
}

ParseTreeLeaf::ParseTreeLeaf(RuleItem *ruleItem) : ParseTreeNode(ruleItem) {

}

std::string ParseTreeLeaf::getNodeName() const {
    if (token == nullptr) {
        return symbol->getSymbolName();
    }
    return token->getText();
}

ASTNode *ParseTreeLeaf::toASTNode() {
    if (getToken() == nullptr) {
        return nullptr;
    }
    if (getToken()->getTokenType() == TokenType::number) {
        return new NumberLiteral(getToken());
    } else if (getToken()->getTokenType() == TokenType::string) {
        return new StringLiteral(getToken());
    } else if (getToken()->getTokenType() == TokenType::identifier) {
        return new Identifier(getToken());
    }
    return nullptr;
}

ParseTreeNonLeaf::ParseTreeNonLeaf(RuleItem *ruleItem) : ParseTreeNode(ruleItem) {

}

bool ParseTreeNonLeaf::isLeaf() {
    return false;
}

std::string ParseTreeNonLeaf::getNodeName() const {
    return "NonLeaf: " + symbol->getSymbolName();
}

ASTNode *ParseTreeNonLeaf::toASTNode() {
    if (getRuleItem()->getSymbolName() == NS_PROGRAM) {
        // program结点
        checkChildNum(3);
        auto builder = OpNodeProgram::Builder();
        auto stmt = getChild(0)->toASTNode();
        if (stmt != nullptr) {
            builder.appendChild(stmt);
        }
        auto programStar = getChild(2);
        while (programStar->childNum() > 0 && !programStar->getChild(0)->isLeaf()) {
            // 将多个连续的program合成一个
            auto program = programStar->getChild(0);
            stmt = program->getChild(0)->toASTNode();
            if (stmt != nullptr) {
                builder.appendChild(stmt);
            }
            programStar = program->getChild(2);
        }
        return builder.build();
    } else if (getRuleItem()->getSymbolName() == NS_STATEMENT_OR_NONE) {
        // statementOrNone结点,孩子可能是statement也可能是空
        return parseChildDirectly();
    } else if (getRuleItem()->getSymbolName() == NS_LINE_END) {
        // 行尾标识符，孩子可能是eol也可能是;，目前暂不解析
        return nullptr;
    } else if (getRuleItem()->getSymbolName() == NS_PROGRAM_STAR) {
        // program的右递归结点，应在program结点中处理
        throw ParseException("programStar should be parsed in program node");
    } else if (getRuleItem()->getSymbolName() == NS_STATEMENT) {
        // statement结点
        if (childNum() == 0) {
            throw ParseException("statement has no child");
        }
        if (getChild(0)->getRuleItem()->getSymbolName() == RW_IF) {
            // if语句
            checkChildNum(4);
            auto builder = OpNodeIf::Builder();
            builder.setCondition(getChild(1)->toASTNode());
            builder.setRunBody(getChild(2)->toASTNode());
            builder.setElsePart(getChild(3)->toASTNode());
            return builder.build();
        } else if (getChild(0)->getRuleItem()->getSymbolName() == RW_WHILE) {
            // while语句
            checkChildNum(3);
            auto builder = OpNodeWhile::Builder();
            builder.setCondition(getChild(1)->toASTNode());
            builder.setRunBody(getChild(2)->toASTNode());
            return builder.build();
        } else {
            checkChildNum(1);
            return parseChildDirectly();
        }
    } else if (getRuleItem()->getSymbolName() == NS_EXPR) {
        // expr结点
        checkChildNum(2);
        return getChild(1)->toASTNode();
    } else if (getRuleItem()->getSymbolName() == NS_EXPR_STAR) {
        // exprStar结点，可能是空也可能是运算符加expr
        if (childNum() == 2) {
            auto builder = OpNodeBinaryExpr::Builder();
            builder.setLeftNode(getFather()->getChild(0)->toASTNode());
            builder.setToken(getChild(0)->getToken());
            builder.setRightNode(getChild(1)->toASTNode());
            return builder.build();
        }
        return getFather()->getChild(0)->toASTNode();
    } else if (getRuleItem()->getSymbolName() == NS_BLOCK) {
        // block 结点
        checkChildNum(4);
        auto builder = OpNodeBlock::Builder();
        auto stmt = getChild(1)->toASTNode();
        if (stmt != nullptr) {
            builder.appendChild(stmt);
        }
        auto blockStar = getChild(2);
        while (blockStar->childNum() == 3) {
            stmt = blockStar->getChild(1)->toASTNode();
            if (stmt != nullptr) {
                builder.appendChild(stmt);
            }
            blockStar = blockStar->getChild(2);
        }
        return builder.build();
    } else if (getRuleItem()->getSymbolName() == NS_BLOCK_STAR) {
        // blockStar结点，其孩子可能是block也可能是空
        throw ParseException("blockStar should be parsed by Block");
    } else if (getRuleItem()->getSymbolName() == NS_STATEMENT_STAR) {
        // statementStar结点，此结点命名不太好，其意思是孩子可能是else也可能是空
        if (childNum() == 2) {
            if (getChild(0)->getRuleItem()->getSymbolName() != RW_ELSE) {
                throw ParseException("statementStar(else) parse fail，can't find else");
            }
            auto builder = OpNodeElse::Builder();
            builder.setRunBody(getChild(1)->toASTNode());
            return builder.build();
        }
        return parseChildDirectly();
    } else if (getRuleItem()->getSymbolName() == NS_SIMPLE) {
        // simple结点
        checkChildNum(2);
        auto simpleStmt = getChild(1)->toASTNode();
        if (simpleStmt != nullptr) {
            auto *simpleStmtModify = getChild(0)->toASTNode();
            auto builder = OpNodeSimple::Builder();
            builder.setSimpleStmt(simpleStmt);
            builder.setReturnStmt(simpleStmtModify != nullptr && simpleStmtModify->toString() == RW_RETURN);
            return builder.build();
        }
        return nullptr;
    } else if (getRuleItem()->getSymbolName() == NS_FACTOR) {
        // factor结点
        if (childNum() == 2) {
            auto opChild = getChild(0);
            if (opChild->getToken() != nullptr && opChild->getToken()->getTokenType() == TokenType::op) {
                auto builder = OpNodeSingleExpr::Builder();
                builder.setOpToken(opChild->getToken());
                builder.setFactor(getChild(1)->toASTNode());
                return builder.build();
            } else {
                throw ParseException("factor has no such grammar");
            }
        }
        return parseChildDirectly();
    } else if (getRuleItem()->getSymbolName() == NS_PRIMARY) {
        // primary结点
        if (childNum() == 4 && getChild(0)->getRuleItem()->getSymbolName() == "[") {
            // 数组
            auto builder = NewNodeArray::Builder();
            auto *elementsOrNone = getChild(1);
            if (elementsOrNone->getChild(0)->isLeaf()) {
                // 无元素
                return builder.build();
            }
            auto *elements = elementsOrNone->getChild(0);
            builder.addElement(elements->getChild(0)->toASTNode());
            for (auto *elementsStar = elements->getChild(1);
                 elementsStar->childNum() == 2;
                 elementsStar = elements->getChild(1)) {
                elements = elementsStar->getChild(1);
                builder.addElement(elements->getChild(0)->toASTNode());
            }
            return builder.build();
        } else if (childNum() == 4 && getChild(0)->getRuleItem()->getSymbolName() == "(") {
            // 表达式，需要判别是否是函数调用
            // TODO 函数支持
            auto builder = DecorateNodePrimary::Builder();
            builder.setExprNode(getChild(1)->toASTNode());
            auto *expr = builder.build();
        } else if (childNum() == 2 && getChild(0)->getToken() != nullptr
                   && getChild(0)->getToken()->getTokenType() == TokenType::number) {
            // 数字，需判别有没有小数
            if (getChild(1)->childNum() == 2) {
                return new NumberLiteral(getChild(0)->getToken(), getChild(1)->getChild(1)->getToken());
            }
            return getChild(0)->toASTNode();
        } else if (childNum() == 3 && getChild(0)->getToken() != nullptr
                   && getChild(1)->getToken()->getTokenType() == TokenType::identifier) {
            // 标识符的情况，需要判别有函数调用以及对象实例化
            auto *newNode = getChild(0)->toASTNode();
            if (newNode != nullptr && newNode->toString() == RW_NEW) {
                // TODO 新建对象
            }
            // TODO 判读是否有函数调用
        } else {
            // STRING
            checkChildNum(1);
            return parseChildDirectly();
        }
    } else if (getRuleItem()->getSymbolName() == NS_PROGRAM_BODY) {
        // programBody 结点，其子节点可能空也可能是函数定义/类定义/语句
        return parseChildDirectly();
    } else if (getRuleItem()->getSymbolName() == NS_RETURN) {
        // 判断语句中表达式前面有没有修饰符，目前只有return
        return parseChildDirectly();
    } else if (getRuleItem()->getSymbolName() == NS_PRIMARY_STAR) {
        // primaryStar 结点，判断是否有函数调用，右递归
    } else if (getRuleItem()->getSymbolName() == NS_FUNC) {
        // func 结点，函数声明
    } else if (getRuleItem()->getSymbolName() == NS_POSTFIX) {
        // postfix 结点，函数调用
    } else if (getRuleItem()->getSymbolName() == NS_POSTFIX_OR_NONE) {
        // postfixOrNone 结点，是否有args
        return parseChildDirectly();
    } else if (getRuleItem()->getSymbolName() == NS_PARAM) {
        // param 结点，函数声明参数
    } else if (getRuleItem()->getSymbolName() == NS_PARAMS) {
        // params 结点，多个函数声明参数
    } else if (getRuleItem()->getSymbolName() == NS_PARAMS_STAR) {
        // params 的递归结点，应在params结点中处理
    } else if (getRuleItem()->getSymbolName() == NS_PARAM_LIST) {
        // param_list 结点，函数声明的那个括号，里面可能有参数/无参数/多个参数
    } else if (getRuleItem()->getSymbolName() == NS_PARAM_LIST_OR_NONE) {
        // paramListOrNone 结点，可能有paramList
        return parseChildDirectly();
    } else if (getRuleItem()->getSymbolName() == NS_ARGS) {
        // args 结点，函数调用的参数列表
    } else if (getRuleItem()->getSymbolName() == NS_ARGS_STAR) {
        // args的递归结点，应在args结点中处理
    } else if (getRuleItem()->getSymbolName() == NS_DECIMALS) {
        // decimals 结点，表示是否有小数，应在primary结点的数字部分一起处理
    } else if (getRuleItem()->getSymbolName() == NS_CLASS) {
        // class 结点，类的声明
    } else if (getRuleItem()->getSymbolName() == NS_EXTENDS) {
        // extends 结点，表示是否有继承
    } else if (getRuleItem()->getSymbolName() == NS_CLASS_BODY) {
        // classBody 结点，标识类声明的内部
    } else if (getRuleItem()->getSymbolName() == NS_CLASS_BODY_STAR) {
        // classBodyStar 结点，与blockStar结点类似，标识0个或多个member，应在classBody中处理
    } else if (getRuleItem()->getSymbolName() == NS_MEMBER_OR_NONE) {
        // memberOrNone 结点，表示是否有member结点
        return parseChildDirectly();
    } else if (getRuleItem()->getSymbolName() == NS_MEMBER) {
        // member 结点，表示类里面的成员，可能是simple也可能是方法，还要判断可见性修饰符
    } else if (getRuleItem()->getSymbolName() == NS_MEMBER_STAR) {
        // memberStar 结点，表示是simple还是方法
    } else if (getRuleItem()->getSymbolName() == NS_STATIC_OR_NONE) {
        // staticOrNone 结点，表示是否有static保留字
        return parseChildDirectly();
    } else if (getRuleItem()->getSymbolName() == NS_ELEMENTS) {
        // elements 结点，表示数组[]内部的表达式
    } else if (getRuleItem()->getSymbolName() == NS_ELEMENTS_OR_NONE) {
        // elementsOrNone 结点，表示有无element结点
        return parseChildDirectly();
    } else if (getRuleItem()->getSymbolName() == NS_ELEMENTS_STAR) {
        // elements的递归结点，应在elements结点中处理
    } else if (getRuleItem()->getSymbolName() == NS_NEW) {
        // new 结点，表示是否有new关键词
        return parseChildDirectly();
    }
    return nullptr;
}

ASTNode *ParseTreeNonLeaf::parseChildDirectly() {
    if (childNum() > 0) {
        return getChild(0)->toASTNode();
    }
    return nullptr;
}
