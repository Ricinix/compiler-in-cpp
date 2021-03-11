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


ParseTreeLeaf::ParseTreeLeaf(RuleItem *ruleItem, Token* token_p) : ParseTreeNode(ruleItem, token_p) {

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
        if (childNum() != 3) {
            throw ParseException("program结点解析失败");
        }
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
        // programStar结点，孩子可能是program也可能是空
        return parseChildDirectly();
    } else if (getRuleItem()->getSymbolName() == NS_STATEMENT) {
        // statement结点
        if (childNum() == 0) {
            throw ParseException("statement has no child");
        }
        if (getChild(0)->getRuleItem()->getSymbolName() == RW_IF) {
            // if语句
            if (childNum() != 4) {
                throw ParseException("statement的if解释必须要有4个孩子结点");
            }
            auto builder = OpNodeIf::Builder();
            builder.setCondition(getChild(1)->toASTNode());
            builder.setRunBody(getChild(2)->toASTNode());
            builder.setElsePart(getChild(3)->toASTNode());
            return builder.build();
        } else if (getChild(0)->getRuleItem()->getSymbolName() == RW_WHILE) {
            // while语句
            if (childNum() != 3) {
                throw ParseException("statement的while解释必须要有3个孩子结点");
            }
            auto builder = OpNodeWhile::Builder();
            builder.setCondition(getChild(1)->toASTNode());
            builder.setRunBody(getChild(2)->toASTNode());
            return builder.build();
        } else {
            return parseChildDirectly();
        }
    } else if (getRuleItem()->getSymbolName() == NS_EXPR) {
        // expr结点
        if (childNum() != 2) {
            throw ParseException("expr的子节点必须得有2个");
        }
        return getChild(1)->toASTNode();
    } else if (getRuleItem()->getSymbolName() == NS_EXPR_STAR) {
        // exprStar结点，可能是空也可能是运算符加expr
        if (childNum() == 2){
            auto builder = OpNodeBinaryExpr::Builder();
            builder.setLeftNode(getFather()->getChild(0)->toASTNode());
            builder.setToken(getChild(0)->getToken());
            builder.setRightNode(getChild(1)->toASTNode());
            return builder.build();
        }
        return getFather()->getChild(0)->toASTNode();
    } else if (getRuleItem()->getSymbolName() == NS_BLOCK) {
        // block 结点
        if (childNum() != 4) {
            throw ParseException("block结点孩子个数必须为4个");
        }
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
        throw ParseException("blockStar结点应由Block结点解析");
    } else if (getRuleItem()->getSymbolName() == NS_STATEMENT_STAR) {
        // statementStar结点，此结点命名不太好，其意思是孩子可能是else也可能是空
        if (childNum() == 2) {
            if (getChild(0)->getRuleItem()->getSymbolName() != RW_ELSE) {
                throw ParseException("statementStar(else)结点解析错误，找不到关键词else");
            }
            auto builder = OpNodeElse::Builder();
            builder.setRunBody(getChild(1)->toASTNode());
            return builder.build();
        }
        return parseChildDirectly();
    } else if (getRuleItem()->getSymbolName() == NS_SIMPLE) {
        // simple结点
        if (childNum() != 1) {
            throw ParseException("simple结点孩子个数必须为1");
        }
        auto simpleStmt = getChild(0)->toASTNode();
        if (simpleStmt != nullptr) {
            auto builder = OpNodeSimple::Builder();
            builder.setSimpleStmt(simpleStmt);
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
                throw ParseException("factor结点中无该文法");
            }
        }
        return parseChildDirectly();
    } else if (getRuleItem()->getSymbolName() == NS_PRIMARY) {
        // primary结点
        if (childNum() == 3) {
            auto builder = DecorateNodePrimary::Builder();
            builder.setExprNode(getChild(1)->toASTNode());
            return builder.build();
        } else if (childNum() != 1) {
            throw ParseException("primary结点孩子个数错误: " + std::to_string(childNum()));
        }
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
