//
// Created by laugh on 2021/3/1.
//

#include "ParseTree.h"
#include <iostream>

ParseTreeNode *ParseTree::getRoot() {
    return root;
}

void ParseTree::setRoot(ParseTreeNode *node) {
    delete root; // 因为delete空指针无作用，所以不判空
    root = node;
}

std::ostream &operator<<(std::ostream &os, const ParseTree &tree) {
    std::ostringstream fmt;
    tree.printTree(tree.root, fmt);
    os << ">>>>>>>>>>ParseTree>>>>>>>>>>" << std::endl;
    os << fmt.str() << std::endl;
    os << "<<<<<<<<<<ParseTree<<<<<<<<<<";
    return os;
}

void ParseTree::printTree(ParseTreeNode *node, std::ostringstream &fmt) const {
    if (node == nullptr) {
        fmt << "null";
        return;
    }
    fmt << node->getRuleItem()->getSymbolName();
    if (node->childNum() == 0) {
        return;
    }
    fmt << "(";
    for (int i = 0; i < node->childNum(); ++i) {
        printTree(node->getChild(i), fmt);
        fmt << ", ";
    }
    fmt << ")";
}

