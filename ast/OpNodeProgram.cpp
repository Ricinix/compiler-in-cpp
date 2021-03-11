//
// Created by laugh on 2021/3/3.
//

#include "OpNodeProgram.h"

void OpNodeProgram::Builder::appendChild(ASTNode *node) {
    programSet.push_back(node);
}

OpNodeProgram *OpNodeProgram::Builder::build() {
    return new OpNodeProgram(programSet);
}

void OpNodeProgram::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}

OpNodeProgram::OpNodeProgram(const std::vector<ASTNode *> &v) : ASTList(v) {

}

std::string OpNodeProgram::toString() const {
    return "program";
}
