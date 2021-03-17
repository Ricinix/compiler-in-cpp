//
// Created by laugh on 2021/3/3.
//

#include "OpNodeProgram.h"
#include "DefineNodeFunction.h"
#include <algorithm>

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
    for (auto &child : defineList) {
        if (node->getType() == ASTNodeType::clz && child->getType() == ASTNodeType::clz
            && child->toString() == node->toString()) {
            // 同名class则抛弃
            return;
        } else if (node->getType() == ASTNodeType::func && child->getType() == ASTNodeType::func) {
            // 同一个函数则抛弃
            auto *funcNode = dynamic_cast<DefineNodeFunction *>(node);
            auto *funcChild = dynamic_cast<DefineNodeFunction *>(child);
            if (funcNode != nullptr && funcChild != nullptr && funcNode->getHashMsg() == funcChild->getHashMsg()) {
                return;
            }
        }
    }
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

int OpNodeProgram::defineNum() {
    return defineList.size();
}

ASTNode *OpNodeProgram::getDefineNum(int i) {
    return defineList[i];
}

int OpNodeProgram::stmtNum() {
    return stmtList.size();
}

ASTNode *OpNodeProgram::getStmt(int i) {
    return stmtList[i];
}

void OpNodeProgram::addNode(ASTNode *node) {
    if (isDefineNode(node)) {
        addDefineNode(node);
    } else {
        addStmtNode(node);
    }
}

void OpNodeProgram::remove(ASTNode *node) {
    ASTList::remove(node);
    removeChildNoDelete(node);
}

void OpNodeProgram::removeAndDelete(ASTNode *node) {
    removeChildNoDelete(node);
    ASTList::removeAndDelete(node);
}

void OpNodeProgram::removeChildNoDelete(ASTNode *node) {
    if (isDefineNode(node)) {
        // 定义结点
        auto iter = std::find(defineList.cbegin(), defineList.cend(), node);
        defineList.erase(iter, iter + 1);
    } else {
        // 语句结点
        auto iter = std::find(stmtList.cbegin(), stmtList.cend(), node);
        stmtList.erase(iter, iter + 1);
    }
}
