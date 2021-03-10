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
    children.push_back(conditionNode);
    children.push_back(runBodyNode);
}

void OpNodeIf::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}

void OpNodeIf::OpNodeIfBuilder::setCondition(ASTNode *node) {
    condition = node;
}

void OpNodeIf::OpNodeIfBuilder::setRunBody(ASTNode *node) {
    runBody = node;
}

OpNodeIf *OpNodeIf::OpNodeIfBuilder::build() {
    return new OpNodeIf(condition, runBody);
}
