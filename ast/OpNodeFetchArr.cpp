//
// Created by laugh on 2021/3/14.
//

#include "OpNodeFetchArr.h"

void OpNodeFetchArr::genCode(IoUtil &ioUtil) {
    arrName->genCode(ioUtil);
    if (insertNode == nullptr) {
        // 取值
        ioUtil.appendContent("->at(");
        index->genCode(ioUtil);
        ioUtil.appendContent(")");
    } else {
        // 赋值
        ioUtil.appendContent("->insert(");
        index->genCode(ioUtil);
        ioUtil.appendContent(", ");
        insertNode->genCode(ioUtil);
        ioUtil.appendContent(")");
    }
}

OpNodeFetchArr::OpNodeFetchArr(ASTNode *arrNameNode, ASTNode *indexNode) {
    arrName = arrNameNode;
    index = indexNode;
    addChild(arrNameNode);
    addChild(indexNode);
}

std::string OpNodeFetchArr::toString() const {
    return "Arr get";
}

ASTNodeType OpNodeFetchArr::getType() {
    return ASTNodeType::opFetchArr;
}

void OpNodeFetchArr::setInsertNode(ASTNode *node) {
    insertNode = node;
}

void OpNodeFetchArr::Builder::setArrName(ASTNode *arrNameNode) {
    arrName = arrNameNode;
}

void OpNodeFetchArr::Builder::setIndexNode(ASTNode *indexNode) {
    index = indexNode;
}

OpNodeFetchArr *OpNodeFetchArr::Builder::build() {
    return new OpNodeFetchArr(arrName, index);
}
