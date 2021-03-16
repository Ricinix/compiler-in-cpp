//
// Created by laugh on 2021/3/15.
//

#include "OriginObjectNode.h"
#include "CodePrinter.h"

std::string OriginObjectNode::toString() const {
    return "Object";
}

void OriginObjectNode::genCode(IoUtil &ioUtil) {
    init();
    ioUtil.appendContent("class Object {\n")
    .appendContent("public: \n");
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
    addMethod(new OriginNodeVirtualMethod("plus", 1));
    addMethod(new OriginNodeVirtualMethod("minus", 1));
    addMethod(new OriginNodeVirtualMethod("divide", 1));
    addMethod(new OriginNodeVirtualMethod("times", 1));
    addMethod(new OriginNodeVirtualMethod("mod", 1));
    addMethod(new OriginNodeVirtualMethod("lessThan", 1));
    addMethod(new OriginNodeVirtualMethod("lessEqualThan", 1));
    addMethod(new OriginNodeVirtualMethod("moreThan", 1));
    addMethod(new OriginNodeVirtualMethod("moreEqualThan", 1));
    addMethod(new OriginNodeVirtualMethod("equal", 1));
    addMethod(new OriginNodeVirtualMethod("toString", 1));
    addMethod(new OriginNodeVirtualMethod("hashCode", 1));
    addMethod(new OriginNodeVirtualMethod("at", 1));
    addMethod(new OriginNodeVirtualMethod("removeAt", 1));
    addMethod(new OriginNodeVirtualMethod("insert", 2));
    addMethod(new OriginNodeVirtualMethod("clear", 0));
    addMethod(new OriginNodeVirtualMethod("size", 0));
}

void OriginObjectNode::addVirtualMethod(ASTNode *methodNode) {
    if (methodNode->getType() != ASTNodeType::method) {
        return;
    }
    auto *method = dynamic_cast<DecorateNodeMethod *>(methodNode);
    if (method == nullptr || method->getHashMsg().empty()) {
        return;
    }
    for (auto &m : methodSet) {
        if (m->getHashMsg() == method->getHashMsg()) {
            return;
        }
    }
    addMethod(new OriginNodeVirtualMethod(method));
}

void OriginTrueNode::genCode(IoUtil &ioUtil) {
    ioUtil.appendContent(
            "class True : public Object {\n"
            "public:\n"
            "    static True *newObj() {\n"
            "        return new True;\n"
            "    }\n"
            "};\n"
    );
    ioUtil.newLine();
}

std::string OriginTrueNode::toString() const {
    return "True";
}
