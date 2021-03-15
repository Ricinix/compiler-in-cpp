//
// Created by laugh on 2021/3/11.
//

#include "DefineNodeObject.h"

std::string DefineNodeObject::toString() const {
    return "obj " + className->toString();
}

DefineNodeObject::DefineNodeObject(ASTNode *name, ASTNode *extendNode, std::vector<DefineNodeDomain *> &domains,
                                   std::vector<DecorateNodeMethod *> &methods) {
    className = name;
    extendObj = extendNode;
    domainSet = domains;
    methodSet = methods;
    addChild(name);
    if (extendNode != nullptr) {
        addChild(extendNode);
    }
    for (auto &domain : domains) {
        addChild(domain);
    }
    for (auto &method : methods) {
        addChild(method);
    }
}

void DefineNodeObject::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}

void DefineNodeObject::addDomain(DefineNodeDomain *domain) {
    for (auto &node : domainSet) {
        if (domain->toString() == node->toString()) {
            return;
        }
    }
    domainSet.push_back(domain);
    addChild(domain);
}

void DefineNodeObject::addMethod(DecorateNodeMethod *method) {
    for (auto &node : methodSet) {
        if (method->getHashMsg() == node->getHashMsg()) {
            return;
        }
    }
    methodSet.push_back(method);
    addChild(method);
}

void DefineNodeObject::Builder::setClassName(ASTNode *name) {
    className = name;
}

DefineNodeObject *DefineNodeObject::Builder::build() {
    return new DefineNodeObject(className, extendObj, domainSet, methodSet);
}

void DefineNodeObject::Builder::addDomain(DefineNodeDomain *domain) {
    domainSet.push_back(domain);
}

void DefineNodeObject::Builder::addMethod(DecorateNodeMethod *method) {
    methodSet.push_back(method);
}

void DefineNodeObject::Builder::setExtendObj(ASTNode *extendNode) {
    extendObj = extendNode;
}
