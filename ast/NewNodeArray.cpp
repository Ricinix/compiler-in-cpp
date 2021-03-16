//
// Created by laugh on 2021/3/14.
//

#include "NewNodeArray.h"

NewNodeArray::NewNodeArray(std::vector<ASTNode *> &elementList) : ASTList(elementList) {
    elements = elementList;
}

std::string NewNodeArray::toString() const {
    return "new arr";
}

void NewNodeArray::genCode(IoUtil &ioUtil) {
    ioUtil.appendContent("Array::newObj(");
    if (!elements.empty()) {
        ioUtil.appendContent("{");
        for (int i = 0; i < elements.size(); ++i) {
            elements[i]->genCode(ioUtil);
            if (i != elements.size() - 1) {
                ioUtil.appendContent(", ");
            }
        }
        ioUtil.appendContent("}");
    }
    ioUtil.appendContent(")");
}

ASTNodeType NewNodeArray::getType() {
    return ASTNodeType::newArr;
}

void NewNodeArray::Builder::addElement(ASTNode *element) {
    elements.push_back(element);
}

NewNodeArray *NewNodeArray::Builder::build() {
    return new NewNodeArray(elements);
}
