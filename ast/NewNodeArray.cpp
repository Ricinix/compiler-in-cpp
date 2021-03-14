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
    ASTList::genCode(ioUtil);
}

void NewNodeArray::Builder::addElement(ASTNode *element) {
    elements.push_back(element);
}

NewNodeArray *NewNodeArray::Builder::build() {
    return new NewNodeArray(elements);
}
