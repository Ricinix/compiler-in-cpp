//
// Created by laugh on 2021/3/11.
//

#include "DecorateNodePrimary.h"

DecorateNodePrimary::DecorateNodePrimary(ASTNode *exprNode) {
    expr = exprNode;
    addChild(exprNode);
}

void DecorateNodePrimary::genCode(IoUtil &ioUtil) {
    ioUtil.appendContent("(");
    expr->genCode(ioUtil);
    ioUtil.appendContent(")");
}

std::string DecorateNodePrimary::toString() const {
    return "(expr)";
}

void DecorateNodePrimary::Builder::setExprNode(ASTNode *exprNode) {
    expr = exprNode;
}

DecorateNodePrimary *DecorateNodePrimary::Builder::build() {
    return new DecorateNodePrimary(expr);
}
