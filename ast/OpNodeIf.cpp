//
// Created by laugh on 2021/3/3.
//

#include "OpNodeIf.h"

std::unique_ptr<ASTNode> OpNodeIf::work() {
    return nullptr;
}

OpNodeIf::OpNodeIf(ASTNode *conditionNode, ASTNode *runBodyNode) {
    condition = conditionNode;
    runBody = runBodyNode;
    addChild(conditionNode);
    addChild(runBodyNode);
}

void OpNodeIf::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}

void OpNodeIf::Builder::setCondition(ASTNode *node) {
    condition = node;
}

void OpNodeIf::Builder::setRunBody(ASTNode *node) {
    runBody = node;
}

OpNodeIf *OpNodeIf::Builder::build() {
    return new OpNodeIf(condition, runBody);
}
