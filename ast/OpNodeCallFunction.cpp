//
// Created by laugh on 2021/3/14.
//

#include "OpNodeCallFunction.h"

std::string OpNodeCallFunction::toString() const {
    return "func";
}

OpNodeCallFunction::OpNodeCallFunction(std::vector<ASTNode *> &argList, ASTNode *funcName) {
    functionName = funcName;
    addChild(funcName);
    for (auto &arg : argList) {
        addChild(arg);
    }
}

void OpNodeCallFunction::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}

void OpNodeCallFunction::Builder::setFunctionName(ASTNode *funcName) {
    functionName = funcName;
}

OpNodeCallFunction *OpNodeCallFunction::Builder::build() {
    return new OpNodeCallFunction(args, functionName);
}

void OpNodeCallFunction::Builder::addArg(ASTNode *arg) {
    args.push_back(arg);
}
