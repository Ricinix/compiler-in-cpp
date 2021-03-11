//
// Created by laugh on 2021/3/3.
//

#include "OpNodeIf.h"

std::unique_ptr<ASTNode> OpNodeIf::work() {
    return nullptr;
}

OpNodeIf::OpNodeIf(ASTNode *conditionNode, ASTNode *runBodyNode, ASTNode *elseNode) {
    condition = conditionNode;
    runBody = runBodyNode;
    elsePart = elseNode;
    addChild(conditionNode);
    addChild(runBodyNode);
    addChild(elseNode);
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
    return new OpNodeIf(condition, runBody, elsePart);
}

void OpNodeIf::Builder::setElsePart(ASTNode *node) {
    elsePart = node;
}
