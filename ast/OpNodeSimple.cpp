//
// Created by laugh on 2021/3/11.
//

#include "OpNodeSimple.h"

void OpNodeSimple::Builder::setSimpleStmt(ASTNode *node) {
    simpleStmt = node;
}

OpNodeSimple *OpNodeSimple::Builder::build() {
    return new OpNodeSimple(simpleStmt);
}

OpNodeSimple::OpNodeSimple(ASTNode *simpleStmtNode) {
    simpleStmt = simpleStmtNode;
    addChild(simpleStmtNode);
}

void OpNodeSimple::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}
