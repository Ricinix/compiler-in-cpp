//
// Created by laugh on 2021/3/11.
//

#include "OpNodeElse.h"

void OpNodeElse::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}

OpNodeElse::OpNodeElse(ASTNode *runBodyNode) {
    runBody = runBodyNode;
}

std::string OpNodeElse::toString() const {
    return "else";
}

void OpNodeElse::Builder::setRunBody(ASTNode *runBodyNode) {
    runBody = runBodyNode;
}

OpNodeElse *OpNodeElse::Builder::build() {
    return new OpNodeElse(runBody);
}
