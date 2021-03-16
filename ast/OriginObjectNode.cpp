//
// Created by laugh on 2021/3/15.
//

#include "OriginObjectNode.h"
#include "CodePrinter.h"

OriginObjectNode::OriginObjectNode() : DefineNodeObject(nullptr, nullptr, domainSet, methodSet) {

}

std::string OriginObjectNode::toString() const {
    return "Object";
}

void OriginObjectNode::genCode(IoUtil &ioUtil) {
    init();
    ioUtil.appendContent("class Object {\n");
    for (auto &method : methodSet) {
        method->genCode(ioUtil);
    }
    ioUtil.appendContent("}\n");
}

void OriginObjectNode::addDomain(DefineNodeDomain *domain) {
    DefineNodeObject::addDomain(domain);
    domainSet.push_back(domain);
}

void OriginObjectNode::addMethod(DecorateNodeMethod *method) {
    DefineNodeObject::addMethod(method);
    methodSet.push_back(method);
}

void OriginObjectNode::init() {
    if (isInit) {
        return;
    }
    isInit = true;
    addMethod(new OriginNodePublicMethod(
            "static Object *newObj() {\n"
            "        return new Object;\n"
            "    }\n"
    ));
    addMethod(new OriginNOdeVirtualMethod("plus", 1));
    addMethod(new OriginNOdeVirtualMethod("minus", 1));
    addMethod(new OriginNOdeVirtualMethod("divide", 1));
    addMethod(new OriginNOdeVirtualMethod("times", 1));
    addMethod(new OriginNOdeVirtualMethod("mod", 1));
    addMethod(new OriginNOdeVirtualMethod("lessThan", 1));
    addMethod(new OriginNOdeVirtualMethod("lessEqualThan", 1));
    addMethod(new OriginNOdeVirtualMethod("moreThan", 1));
    addMethod(new OriginNOdeVirtualMethod("moreEqualThan", 1));
    addMethod(new OriginNOdeVirtualMethod("equal", 1));
    addMethod(new OriginNOdeVirtualMethod("toString", 1));
    addMethod(new OriginNOdeVirtualMethod("hashCode", 1));
    addMethod(new OriginNOdeVirtualMethod("at", 1));
    addMethod(new OriginNOdeVirtualMethod("removeAt", 1));
    addMethod(new OriginNOdeVirtualMethod("insert", 2));
    addMethod(new OriginNOdeVirtualMethod("clear", 0));
}

void OriginObjectNode::addVirtualMethod(ASTNode *methodNode) {
    if (methodNode->getType() != ASTNodeType::method) {
        return;
    }
    auto *method = dynamic_cast<DecorateNodeMethod *>(methodNode);
    if (method == nullptr) {
        return;
    }
    for (auto &m : methodSet) {
        if (m->getHashMsg() == method->getHashMsg()) {
            return;
        }
    }
    addMethod(new OriginNOdeVirtualMethod(method));
}

void OriginTrueNode::init() {
    if (isInit) {
        return;
    }
    isInit = true;
    addMethod(new OriginNodePublicMethod(
            "static True *newObj() {\n"
            "        return new True;\n"
            "    }\n"
    ));
}

void OriginTrueNode::genCode(IoUtil &ioUtil) {
    init();
    ioUtil.appendContent("class True : public Object {\n");
    for (auto &method : methodSet) {
        method->genCode(ioUtil);
    }
    ioUtil.appendContent("}\n");
}
