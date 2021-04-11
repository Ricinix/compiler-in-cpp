//
// Created by laugh on 2021/3/15.
//

#include <sstream>
#include "DecorateNodeMethod.h"
#include "../domain/exception.h"

DecorateNodeMethod::DecorateNodeMethod(DefineNodeFunction *funcNode, bool isStaticMethod) {
    func = funcNode;
    isStatic = isStaticMethod;
    addChild(funcNode);
}

void DecorateNodeMethod::genCode(IoUtil &ioUtil) {
    if (genConstructor(ioUtil)) {
        return;
    }
    if (func->child(0)->toString()[0] == '_') {
        ioUtil.appendContent("private:\n");
    } else {
        ioUtil.appendContent("public:\n");
    }
    if (isStatic) {
        ioUtil.appendContent("static ");
    } else {
        func->setNeedOverride(true);
    }
    func->genCode(ioUtil);
}

std::string DecorateNodeMethod::toString() const {
    return "Method";
}

std::string DecorateNodeMethod::getHashMsg() const {
    if (func == nullptr) {
        return "";
    }
    return func->toString() + "_" + std::to_string(func->paramNum());
}

ASTNodeType DecorateNodeMethod::getType() {
    if (isConstructor()) {
        return ASTNodeType::constructor;
    }
    return ASTNodeType::method;
}

std::string DecorateNodeMethod::getMethodName() {
    return func->toString();
}

int DecorateNodeMethod::getParamNum() {
    return func->paramNum();
}

bool DecorateNodeMethod::isConstructor() {
    return func->toString() == "init";
}

bool DecorateNodeMethod::genConstructor(IoUtil &ioUtil) {
    if (!isConstructor()) {
        return false;
    }
    // 先生成c++的构造器
    ioUtil.appendContent("public:\n")
            .appendContent("explicit ")
            .appendContent(getFather()->toString());
    printParamList(ioUtil, true);
    func->getRunBody()->genCode(ioUtil);
    // 再生成hook一层的构造器
    ioUtil.appendContent("static Object *newObj");
    printParamList(ioUtil, true);
    ioUtil.appendContent("{\n")
            .appendContent("return new ")
            .appendContent(getFather()->toString());
    printParamList(ioUtil, false);
    ioUtil.appendContent(";\n")
            .appendContent("}\n");
    return true;
}

void DecorateNodeMethod::printParamList(IoUtil &ioUtil, bool printType) {
    ioUtil.appendContent("(");
    for (int i = 0; i < func->paramNum(); ++i) {
        if (printType) {
            ioUtil.appendContent("Object *");
        }
        func->getParamName(i)->genCode(ioUtil);
        if (i != func->paramNum() - 1) {
            ioUtil.appendContent(", ");
        }
    }
    ioUtil.appendContent(")");
}

bool DecorateNodeMethod::isStaticMethod() const {
    return isStatic;
}

std::string DecorateNodeMethod::getStaticHashMsg() {
    if (!isStatic) {
        return "";
    }
    if (getFather()->getType() != ASTNodeType::clz) {
        throw ParseException("method's father is not clz");
    }
    std::ostringstream fmt;
    fmt << getFather()->toString() << "::";
    fmt << func->getHashMsg();
    return fmt.str();
}

void DecorateNodeMethod::Builder::setStatic(bool isStaticMethod) {
    isStatic = isStaticMethod;
}

void DecorateNodeMethod::Builder::setFunc(DefineNodeFunction *funcNode) {
    func = funcNode;
}

DecorateNodeMethod *DecorateNodeMethod::Builder::build() {
    return new DecorateNodeMethod(func, isStatic);
}
