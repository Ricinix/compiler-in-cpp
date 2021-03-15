//
// Created by laugh on 2021/3/15.
//

#include "OpNodeImport.h"

std::string OpNodeImport::toString() const {
    return "import";
}

OpNodeImport::OpNodeImport(ASTNode *pathNode) {
    path = pathNode;
    addChild(pathNode);
}

void OpNodeImport::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}

void OpNodeImport::Builder::setPath(ASTNode *pathNode) {
    path = pathNode;
}

OpNodeImport *OpNodeImport::Builder::build() {
    return new OpNodeImport(path);
}
