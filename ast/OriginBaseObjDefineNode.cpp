//
// Created by laugh on 2021/3/16.
//

#include "OriginBaseObjDefineNode.h"

std::string OriginBaseObjDefineNode::toString() const {
    return "Origin Object define";
}

void OriginBaseObjDefineNode::genCode(IoUtil &ioUtil) {
    DefineNodeObject::genCode(ioUtil);
}
