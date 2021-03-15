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
    for (auto &node : v) {
        if (isDefineNode(node)) {
            defineList.push_back(node);
        } else {
            stmtList.push_back(node);
        }
    }
}

std::string OpNodeProgram::toString() const {
    return "program";
}

ASTNodeType OpNodeProgram::getType() {
    return ASTNodeType::program;
}

bool OpNodeProgram::isDefineNode(ASTNode *node) {
    return node->getType() == ASTNodeType::func || node->getType() == ASTNodeType::clz;
}

void OpNodeProgram::addDefineNode(ASTNode *node) {
    defineList.push_back(node);
    addChild(node);
}

void OpNodeProgram::addStmtNode(ASTNode *node) {
    stmtList.push_back(node);
    addChild(node);
}

void OpNodeProgram::insertDefineNode(int i, ASTNode *node) {
    defineList.insert(defineList.cbegin() + i, node);
    insert(i, node);
}
