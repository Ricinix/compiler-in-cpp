//
// Created by laugh on 2021/3/15.
//

#include "DecorateNodeMethod.h"

DecorateNodeMethod::DecorateNodeMethod(DefineNodeFunction *funcNode, bool isStaticMethod) {
    func = funcNode;
    isStatic = isStaticMethod;
    addChild(funcNode);
}

void DecorateNodeMethod::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}

std::string DecorateNodeMethod::toString() const {
    return "Method";
}

std::string DecorateNodeMethod::getHashMsg() const {
    return func->toString() + "_" + std::to_string(func->paramNum());
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
