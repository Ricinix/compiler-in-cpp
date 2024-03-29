//
// Created by laugh on 2021/3/10.
//

#include "OpNodeWhile.h"

void OpNodeWhile::Builder::setCondition(ASTNode *node) {
    condition = node;
}

void OpNodeWhile::Builder::setRunBody(ASTNode *node) {
    runBody = node;
}

OpNodeWhile *OpNodeWhile::Builder::build() {
    return new OpNodeWhile(condition, runBody);
}

void OpNodeWhile::genCode(IoUtil &ioUtil) {
    ioUtil.appendContent("while(");
    condition->genCode(ioUtil);
    ioUtil.appendContent(")");
    runBody->genCode(ioUtil);
}

OpNodeWhile::OpNodeWhile(ASTNode *conditionNode, ASTNode *runBodyNode) {
    condition = conditionNode;
    runBody = runBodyNode;
    addChild(condition);
    addChild(runBody);
}

std::string OpNodeWhile::toString() const {
    return "while";
}

ASTNodeType OpNodeWhile::getType() {
    return ASTNodeType::opWhile;
}
