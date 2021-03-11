//
// Created by laugh on 2021/3/11.
//

#include "OpNodeBlock.h"

OpNodeBlock::OpNodeBlock(const std::vector<ASTNode *> &v) : ASTList(v) {

}

void OpNodeBlock::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}

std::string OpNodeBlock::toString() const {
    return "{}";
}

void OpNodeBlock::Builder::appendChild(ASTNode *node) {
    stmtSet.push_back(node);
}

OpNodeBlock *OpNodeBlock::Builder::build() {
    return new OpNodeBlock(stmtSet);
}
