//
// Created by laugh on 2021/3/3.
//

#include "OpNodeIf.h"

OpNodeIf::OpNodeIf(ASTNode *conditionNode, ASTNode *runBodyNode, ASTNode *elseNode) {
    condition = conditionNode;
    runBody = runBodyNode;
    elsePart = elseNode;
    addChild(conditionNode);
    addChild(runBodyNode);
    addChild(elseNode);
}

void OpNodeIf::genCode(IoUtil &ioUtil) {
    ioUtil.appendContent("if(");
    condition->genCode(ioUtil);
    ioUtil.appendContent(")");
    runBody->genCode(ioUtil);
    if (elsePart != nullptr) {
        elsePart->genCode(ioUtil);
    }
}

std::string OpNodeIf::toString() const {
    return "if";
}

ASTNodeType OpNodeIf::getType() {
    return ASTNodeType::opIf;
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
