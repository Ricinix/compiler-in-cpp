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
    ASTList::genCode(ioUtil);
}

OpNodeWhile::OpNodeWhile(ASTNode *conditionNode, ASTNode *runBodyNode) {
    condition = conditionNode;
    runBody = runBodyNode;
    children.push_back(condition);
    children.push_back(runBody);
}
