//
// Created by laugh on 2021/3/11.
//

#include "DefineNodeObject.h"

DefineNodeObject::~DefineNodeObject() {
    for (auto &domain : domainSet) {
        delete domain;
        domain = nullptr;
    }
    for (auto &function : functionSet) {
        delete function;
        function = nullptr;
    }
}

std::string DefineNodeObject::toString() const {
    return className;
}

DefineNodeObject::DefineNodeObject(const std::string &name, std::vector<ASTNode *> &domains,
                                   std::vector<ASTNode *> &functions) {
    className = name;
    domainSet = domains;
    functionSet = functions;
    for (auto &domain : domains) {
        addChild(domain);
    }
    for (auto &function : functions) {
        addChild(function);
    }
}

void DefineNodeObject::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}

void DefineNodeObject::Builder::setClassName(const std::string &name) {
    className = name;
}

DefineNodeObject *DefineNodeObject::Builder::build() {
    return new DefineNodeObject(className, domainSet, functionSet);
}

void DefineNodeObject::Builder::addDomain(ASTNode *domain) {
    domainSet.push_back(domain);
}

void DefineNodeObject::Builder::addFunction(ASTNode *function) {
    functionSet.push_back(function);
}
