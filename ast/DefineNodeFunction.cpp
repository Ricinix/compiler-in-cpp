//
// Created by laugh on 2021/3/11.
//

#include "DefineNodeFunction.h"

void DefineNodeFunction::Builder::setFunctionName(ASTNode *funcName) {
    functionName = funcName;
}

void DefineNodeFunction::Builder::addParam(ASTNode *param) {
    params.push_back(param);
}

void DefineNodeFunction::Builder::setRunBody(ASTNode *runPart) {
    runBody = runPart;
}

DefineNodeFunction *DefineNodeFunction::Builder::build() {
    return new DefineNodeFunction(functionName, params, runBody);
}

DefineNodeFunction::DefineNodeFunction(ASTNode *funcName, std::vector<ASTNode *> &paramSet, ASTNode *runPart) : ASTList(paramSet) {
    functionName = funcName;
    params = paramSet;
    runBody = runPart;
    addChild(funcName);
    addChild(runPart);
}

void DefineNodeFunction::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}

std::string DefineNodeFunction::toString() const {
    return functionName->toString();
}

int DefineNodeFunction::paramNum() const {
    return params.size();
}

DefineNodeFunction::DefineNodeFunction() {
    functionName = nullptr;
    runBody = nullptr;
}

ASTNodeType DefineNodeFunction::getType() {
    return ASTNodeType::func;
}

std::string DefineNodeFunction::getHashMsg() {
    return functionName->toString() + "_" + std::to_string(paramNum());
}
