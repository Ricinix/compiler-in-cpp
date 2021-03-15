//
// Created by laugh on 2021/3/11.
//

#include "OpNodeSimple.h"

void OpNodeSimple::Builder::setSimpleStmt(ASTNode *node) {
    simpleStmt = node;
}

OpNodeSimple *OpNodeSimple::Builder::build() {
    return new OpNodeSimple(simpleStmt, isReturnStmt);
}

void OpNodeSimple::Builder::setReturnStmt(bool isReturn) {
    isReturnStmt = isReturn;
}

OpNodeSimple::OpNodeSimple(ASTNode *simpleStmtNode, bool isReturn) {
    simpleStmt = simpleStmtNode;
    isReturnStmt = isReturn;
    addChild(simpleStmtNode);
}

void OpNodeSimple::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}

std::string OpNodeSimple::toString() const {
    if (isReturnStmt) {
        return "return";
    }
    return ";";
}
