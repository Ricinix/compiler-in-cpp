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
    args = argList;
    for (auto &arg : argList) {
        addChild(arg);
    }
}

void OpNodeCallFunction::genCode(IoUtil &ioUtil) {
    functionName->genCode(ioUtil);
    ioUtil.appendContent("(");
    for (int i = 0; i < args.size(); ++i) {
        args[i]->genCode(ioUtil);
        if (i != args.size() -1) {
            ioUtil.appendContent(", ");
        }
    }
    ioUtil.appendContent(")");
}

ASTNodeType OpNodeCallFunction::getType() {
    return ASTNodeType::funcCall;
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
