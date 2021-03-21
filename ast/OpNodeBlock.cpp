//
// Created by laugh on 2021/3/11.
//

#include "OpNodeBlock.h"
#include "../rule/SymbolTable.h"

OpNodeBlock::OpNodeBlock(const std::vector<ASTNode *> &v) : ASTList(v) {

}

void OpNodeBlock::genCode(IoUtil &ioUtil) {
    ioUtil.appendContent("{\n");
    SymbolTable::newCell();
    bool hasReturn = false;
    for (auto &child : children) {
        child->genCode(ioUtil);
        if (child->getType() == ASTNodeType::returnStmt) {
            hasReturn = true;
        }
    }
    if (!hasReturn) {
        // 释放资源(仅在block里没有return资源的情况下，删除在该block里new出来的变量)
        for (int i = 0; i < SymbolTable::getIdNumInTailCell(); ++i) {
            const std::string &id = SymbolTable::getIdByPos(i);
            ioUtil.appendContent("delete " + id + ";\n");
        }
    }
    SymbolTable::popCell();
    if (getFather()->getType() == ASTNodeType::func
        && getFather()->getFather()->getType() != ASTNodeType::constructor && !hasReturn) {
        ioUtil.appendContent("return nullptr;\n");
    }
    ioUtil.appendContent("}\n");
}

std::string OpNodeBlock::toString() const {
    return "{}";
}

ASTNodeType OpNodeBlock::getType() {
    return ASTNodeType::block;
}

void OpNodeBlock::Builder::appendChild(ASTNode *node) {
    stmtSet.push_back(node);
}

OpNodeBlock *OpNodeBlock::Builder::build() {
    return new OpNodeBlock(stmtSet);
}
