//
// Created by laugh on 2021/3/11.
//

#include "DefineNodeDomain.h"

VisibleType DefineNodeDomain::getVisibleType() {
    return type;
}

std::string DefineNodeDomain::getName() {
    return name;
}

DefineNodeDomain::DefineNodeDomain(VisibleType objType, const std::string &objName, ASTNode *initStmtNode) {
    type = objType;
    name = objName;
    initStmt = initStmtNode;
    addChild(initStmtNode);
}

std::string DefineNodeDomain::toString() const {
    return "ObjDomain: " + name;
}

void DefineNodeDomain::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}

void DefineNodeDomain::Builder::setName(const std::string &objName) {
    name = objName;
}

void DefineNodeDomain::Builder::setVisibleType(VisibleType objType) {
    type = objType;
}

void DefineNodeDomain::Builder::setInitStatement(ASTNode *stmt) {
    initStmt = stmt;
}

DefineNodeDomain *DefineNodeDomain::Builder::build() {
    return new DefineNodeDomain(type, name, initStmt);
}
