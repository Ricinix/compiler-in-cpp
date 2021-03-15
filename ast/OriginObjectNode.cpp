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

}

void OriginObjectNode::addDomain(DefineNodeDomain *domain) {
    DefineNodeObject::addDomain(domain);
    domainSet.push_back(domain);
}

void OriginObjectNode::addMethod(DecorateNodeMethod *method) {
    DefineNodeObject::addMethod(method);
    methodSet.push_back(method);
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
