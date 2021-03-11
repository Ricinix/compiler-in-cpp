//
// Created by laugh on 2020/12/29.
//

#include "OpNodeBinaryExpr.h"

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
    ASTList::genCode(ioUtil);
}

std::string OpNodeBinaryExpr::toString() const {
    return token->getText();
}
