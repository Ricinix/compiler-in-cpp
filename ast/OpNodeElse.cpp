//
// Created by laugh on 2021/3/11.
//

#include "OpNodeElse.h"

void OpNodeElse::genCode(IoUtil &ioUtil) {
    ASTNode::genCode(ioUtil);
}

OpNodeElse::OpNodeElse(ASTNode *runBodyNode) {
    runBody = runBodyNode;
}

void OpNodeElse::Builder::setRunBody(ASTNode *runBodyNode) {
    runBody = runBodyNode;
}

OpNodeElse *OpNodeElse::Builder::build() {
    return new OpNodeElse(runBody);
}
