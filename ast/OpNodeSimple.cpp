//
// Created by laugh on 2021/3/11.
//

#include <algorithm>
#include "OpNodeSimple.h"
#include "../rule/SymbolTable.h"

void OpNodeSimple::Builder::setSimpleStmt(ASTNode *node) {
    simpleStmt = node;
}

OpNodeSimple *OpNodeSimple::Builder::build() {
    return new OpNodeSimple(simpleStmt, isReturnStmt);
}

void OpNodeSimple::Builder::setReturnStmt(bool isReturn) {
    isReturnStmt = isReturn;
}

OpNodeSimple::OpNodeSimple(ASTNode *simpleStmtNode, bool isReturn) {
    simpleStmt = simpleStmtNode;
    isReturnStmt = isReturn;
    addChild(simpleStmtNode);
}

void OpNodeSimple::genCode(IoUtil &ioUtil) {
    if (isReturnStmt) {
//        std::vector<std::string> idList;
//        // 检查return后面的表达式有用到啥id，把没用到的id取出来delete掉
//        checkIdList(this, idList);
//        for (int i = 0; i < SymbolTable::getIdNumInTailCell(); ++i) {
//            const std::string id = SymbolTable::getIdByPos(i);
//            if (std::find(idList.cbegin(), idList.cend(), id) != idList.end()) {
//                ioUtil.appendContent("delete " + id + ";\n");
//            }
//        }
        ioUtil.appendContent("return ");
    }
    simpleStmt->genCode(ioUtil);
    ioUtil.appendContent(";\n");
}

std::string OpNodeSimple::toString() const {
    if (isReturnStmt) {
        return "return";
    }
    return ";";
}

ASTNodeType OpNodeSimple::getType() {
    if (isReturnStmt) {
        return ASTNodeType::returnStmt;
    }
    return ASTNodeType::normalStmt;
}

void OpNodeSimple::checkIdList(ASTNode *node, std::vector<std::string> &list) {
    for (int i = 0; i < node->numChildren(); ++i) {
        auto *child = node->child(i);
        if (child->getType() == ASTNodeType::id) {
            list.push_back(child->toString());
            continue;
        } else {
            checkIdList(child, list);
        }
    }
}
