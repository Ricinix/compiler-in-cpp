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
    ioUtil.appendContent("#include <string>\n")
            .appendContent("#include <stdlib.h>\n")
            .appendContent("#include <sstream>\n")
            .appendContent("#include <map>\n")
            .appendContent("#include <iostream>\n")
            .appendContent("#include <initializer_list>\n");

    ioUtil.newLine();
    for (auto &child : defineList) {
        child->genCode(ioUtil);
    }
    ioUtil.appendContent("int main() {\n");
    for (auto &stmt : stmtList) {
        stmt->genCode(ioUtil);
    }
    ioUtil.appendContent("system(\"pause\");\n")
            .appendContent("return 0;\n")
            .appendContent("}\n");
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
