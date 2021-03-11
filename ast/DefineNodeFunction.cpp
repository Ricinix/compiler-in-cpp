//
// Created by laugh on 2021/3/11.
//

#include "DefineNodeFunction.h"

void DefineNodeFunction::Builder::setVisibleType(VisibleType type) {
    visibleType = type;
}

void DefineNodeFunction::Builder::setFunctionName(const std::string &name) {
    functionName = name;
}

void DefineNodeFunction::Builder::addParam(ASTNode *param) {
    params.push_back(param);
}

void DefineNodeFunction::Builder::setRunBody(ASTNode *runPart) {
    runBody = runPart;
}

DefineNodeFunction *DefineNodeFunction::Builder::build() {
    return new DefineNodeFunction(visibleType, functionName, params, runBody);
}

DefineNodeFunction::DefineNodeFunction(VisibleType type, const std::string &name, std::vector<ASTNode *> &paramSet,
                                       ASTNode *runPart) {
    visibleType = type;
    functionName = name;
    params = paramSet;
    runBody = runPart;
    for (auto &param : paramSet) {
        addChild(param);
    }
    addChild(runPart);
}

void DefineNodeFunction::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}

std::string DefineNodeFunction::toString() const {
    return functionName;
}
