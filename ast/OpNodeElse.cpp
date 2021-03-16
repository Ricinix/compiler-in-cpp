//
// Created by laugh on 2021/3/11.
//

#include "OpNodeElse.h"

void OpNodeElse::genCode(IoUtil &ioUtil) {
    ioUtil.appendContent("else ");
    runBody->genCode(ioUtil);
}

OpNodeElse::OpNodeElse(ASTNode *runBodyNode) {
    runBody = runBodyNode;
    addChild(runBodyNode);
}

std::string OpNodeElse::toString() const {
    return "else";
}

ASTNodeType OpNodeElse::getType() {
    return ASTNodeType::opElse;
}

void OpNodeElse::Builder::setRunBody(ASTNode *runBodyNode) {
    runBody = runBodyNode;
}

OpNodeElse *OpNodeElse::Builder::build() {
    return new OpNodeElse(runBody);
}
