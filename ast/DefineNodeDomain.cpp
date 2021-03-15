//
// Created by laugh on 2021/3/11.
//

#include "DefineNodeDomain.h"

DefineNodeDomain::DefineNodeDomain(ASTNode *initStmtNode, bool isStaticDomain) {
    initStmt = initStmtNode;
    isStatic = isStaticDomain;
    addChild(initStmtNode);
}

std::string DefineNodeDomain::toString() const {
    return "ObjDomain: " + initStmt->child(0)->toString();
}

void DefineNodeDomain::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}

void DefineNodeDomain::Builder::setInitStatement(ASTNode *stmt) {
    initStmt = stmt;
}

DefineNodeDomain *DefineNodeDomain::Builder::build() {
    return new DefineNodeDomain(initStmt, isStatic);
}

void DefineNodeDomain::Builder::setStaticDomain(bool isStaticDomain) {
    isStatic = isStaticDomain;
}
