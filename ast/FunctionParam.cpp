//
// Created by laugh on 2021/3/11.
//

#include "FunctionParam.h"

FunctionParam::FunctionParam(Token *t) : ASTLeaf(t) {

}

void FunctionParam::genCode(IoUtil &ioUtil) {
    ASTLeaf::genCode(ioUtil);
}

