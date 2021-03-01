//
// Created by laugh on 2021/3/1.
//

#include "ParseTree.h"

ParseTreeNode *ParseTree::getRoot() {
    return root;
}

void ParseTree::setRoot(ParseTreeNode *node) {
    delete root; // 因为delete空指针无作用，所以不判空
    root = node;
}
