//
// Created by laugh on 2021/3/11.
//

#include "DefineNodeObject.h"
#include "../rule/SymbolTable.h"

std::string DefineNodeObject::toString() const {
    return className->toString();
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
    ioUtil.appendContent("class ");
    className->genCode(ioUtil);
    ioUtil.appendContent(": public ");
    if (extendObj != nullptr) {
        extendObj->genCode(ioUtil);
    } else {
        ioUtil.appendContent("Object");
    }
    ioUtil.appendContent("{\n");
    SymbolTable::newCell();
    for (auto &domain : domainSet) {
        domain->genCode(ioUtil);
    }
    bool hasConstructor = false;
    for (auto &method : methodSet) {
        if (method->isConstructor()) {
            hasConstructor = true;
        }
        method->genCode(ioUtil);
    }
    if (!hasConstructor) {
        genDefaultConstructor(ioUtil);
    }
    SymbolTable::popCell();
    ioUtil.appendContent("}\n");
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

DefineNodeObject::DefineNodeObject() {
    className = nullptr;
    extendObj = nullptr;
}

ASTNodeType DefineNodeObject::getType() {
    return ASTNodeType::clz;
}

void DefineNodeObject::genDefaultConstructor(IoUtil &ioUtil) {
    ioUtil.appendContent("public:\n");
    className->genCode(ioUtil);
    ioUtil.appendContent("() {}\n")
    .appendContent("static ");
    className->genCode(ioUtil);
    ioUtil.appendContent(" *newObj(){\n")
            .appendContent("return new ");
    className->genCode(ioUtil);
    ioUtil.appendContent("}\n");
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
