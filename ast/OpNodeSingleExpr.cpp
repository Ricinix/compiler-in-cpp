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
    ioUtil.appendContent("Number::newObj(0)");
    auto opType = getOpType();
    if (opType == OpType::minus) {
        ioUtil.appendContent("->minus(");
        factor->genCode(ioUtil);
        ioUtil.appendContent(")");
    } else {
        ioUtil.appendContent(token->getText());
        factor->genCode(ioUtil);
    }
}

std::string OpNodeSingleExpr::toString() const {
    return token->getText();
}

ASTNodeType OpNodeSingleExpr::getType() {
    return ASTNodeType::opSingleExpr;
}

OpType OpNodeSingleExpr::getOpType() {
    if (token->getTokenType() == TokenType::op) {
        auto *opToken = dynamic_cast<OpToken *>(token);
        if (opToken != nullptr) {
            return opToken->getOpType();
        }
    }
    return OpType::none;
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
