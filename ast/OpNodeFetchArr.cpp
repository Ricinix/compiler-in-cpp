//
// Created by laugh on 2021/3/14.
//

#include "OpNodeFetchArr.h"

void OpNodeFetchArr::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
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

void OpNodeFetchArr::Builder::setArrName(ASTNode *arrNameNode) {
    arrName = arrNameNode;
}

void OpNodeFetchArr::Builder::setIndexNode(ASTNode *indexNode) {
    index = indexNode;
}

OpNodeFetchArr *OpNodeFetchArr::Builder::build() {
    return new OpNodeFetchArr(arrName, index);
}
