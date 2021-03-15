//
// Created by laugh on 2021/3/14.
//

#include "NewNodeObject.h"

NewNodeObject *NewNodeObject::Builder::build() {
    return new NewNodeObject(objNameId);
}

void NewNodeObject::Builder::setObjName(ASTNode *objName) {
    objNameId = objName;
}

NewNodeObject::NewNodeObject(ASTNode *objNameNode) {
    objNameId = objNameNode;
    addChild(objNameNode);
}

std::string NewNodeObject::toString() const {
    return "new obj";
}

void NewNodeObject::genCode(IoUtil &ioUtil) {
    ASTList::genCode(ioUtil);
}
