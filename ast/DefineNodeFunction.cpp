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
    ioUtil.appendContent("Object *");
    functionName->genCode(ioUtil);
    ioUtil.appendContent("(");
    for (int i = 0; i < paramNum(); ++i) {
        ioUtil.appendContent("Object *");
        params[i]->genCode(ioUtil);
        if (i != paramNum() -1) {
            ioUtil.appendContent(", ");
        }
    }
    ioUtil.appendContent(")");
    if (needOverride) {
        ioUtil.appendContent(" override ");
    }
    runBody->genCode(ioUtil);
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

void DefineNodeFunction::setNeedOverride(bool need) {
    needOverride = need;
}

ASTNode *DefineNodeFunction::getRunBody() {
    return runBody;
}

ASTNode *DefineNodeFunction::getParamName(int i) {
    return params[i];
}
