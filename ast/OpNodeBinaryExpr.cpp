//
// Created by laugh on 2020/12/29.
//

#include "OpNodeBinaryExpr.h"
#include "OpNodeFetchArr.h"
#include "../rule/SymbolTable.h"

void OpNodeBinaryExpr::Builder::setLeftNode(ASTNode *leftNode) {
    left = leftNode;
}

void OpNodeBinaryExpr::Builder::setRightNode(ASTNode *rightNode) {
    right = rightNode;
}

void OpNodeBinaryExpr::Builder::setToken(Token *t) {
    opToken = t;
}

OpNodeBinaryExpr *OpNodeBinaryExpr::Builder::build() {
    return new OpNodeBinaryExpr(left, right, opToken);
}

OpNodeBinaryExpr::OpNodeBinaryExpr(ASTNode *leftNode, ASTNode *rightNode, Token *t) {
    left = leftNode;
    right = rightNode;
    token = t;
    addChild(leftNode);
    addChild(rightNode);
}

void OpNodeBinaryExpr::genCode(IoUtil &ioUtil) {
    if (checkArr()) {
        return;
    }
    if (token->getTokenType() == TokenType::op) {
        auto *opToken = dynamic_cast<OpToken *>(token);
        if (opToken != nullptr) {
            if (opToken->getOpType() == OpType::assign && left->getType() == ASTNodeType::id
                && SymbolTable::insert(left->toString())) {
                ioUtil.appendContent("Object *");
            }
            left->genCode(ioUtil);
            if (opToken->getOpType() == OpType::more) {
                addOp("moreThan", ioUtil);
            } else if (opToken->getOpType() == OpType::moreEqual) {
                addOp("moreEqualThan", ioUtil);
            } else if (opToken->getOpType() == OpType::less) {
                addOp("lessThan", ioUtil);
            } else if (opToken->getOpType() == OpType::lessEqual) {
                addOp("lessEqualThan", ioUtil);
            } else if (opToken->getOpType() == OpType::plus) {
                addOp("plus", ioUtil);
            } else if (opToken->getOpType() == OpType::minus) {
                addOp("minus", ioUtil);
            } else if (opToken->getOpType() == OpType::divide) {
                addOp("divide", ioUtil);
            } else if (opToken->getOpType() == OpType::times) {
                addOp("times", ioUtil);
            } else if (opToken->getOpType() == OpType::mod) {
                addOp("mod", ioUtil);
            } else if (opToken->getOpType() == OpType::equal) {
                addOp("equal", ioUtil);
            } else {
                ioUtil.appendContent(token->getText());
                right->genCode(ioUtil);
            }
        } else {
            left->genCode(ioUtil);
            ioUtil.appendContent(token->getText());
            right->genCode(ioUtil);
        }
    } else {
        left->genCode(ioUtil);
        ioUtil.appendContent(token->getText());
        right->genCode(ioUtil);
    }

}

std::string OpNodeBinaryExpr::toString() const {
    return token->getText();
}

ASTNodeType OpNodeBinaryExpr::getType() {
    return ASTNodeType::opBinaryExpr;
}

void OpNodeBinaryExpr::addOp(const std::string &opName, IoUtil &ioUtil) {
    ioUtil.appendContent("->" + opName + "(");
    right->genCode(ioUtil);
    ioUtil.appendContent(")");
}

/**
 * 如果左值中的是数组，则当前结点将演化为向数组中插入值
 *
 * @return
 */
bool OpNodeBinaryExpr::checkArr() {
    if (token->getTokenType() == TokenType::op && left->getType() == ASTNodeType::opFetchArr) {
        auto *opToken = dynamic_cast<OpToken *>(token);
        if (opToken != nullptr && opToken->getOpType() == OpType::assign) {
            auto *leftArrNode = dynamic_cast<OpNodeFetchArr *>(left);
            if (leftArrNode != nullptr) {
                leftArrNode->setInsertNode(right);
                return true;
            }
        }
    }
    return false;
}
