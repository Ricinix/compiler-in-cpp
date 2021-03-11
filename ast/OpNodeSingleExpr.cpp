//
// Created by laugh on 2021/3/11.
//

#include "OpNodeSingleExpr.h"

OpNodeSingleExpr::OpNodeSingleExpr(ASTNode *factorNode, Token *opToken) {
    token = opToken;
    factor = factorNode;
    addChild(factorNode);
}

void OpNodeSingleExpr::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}

void OpNodeSingleExpr::Builder::setOpToken(Token *t) {
    opToken = t;
}

void OpNodeSingleExpr::Builder::setFactor(ASTNode *node) {
    factor = node;
}

OpNodeSingleExpr *OpNodeSingleExpr::Builder::build() {
    return new OpNodeSingleExpr(factor, opToken);
}
