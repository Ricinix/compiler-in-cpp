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
    std::string intent;
    os << ">>>>>>>>>>ParseTree>>>>>>>>>>" << std::endl;
    tree.printTree(tree.root, os, intent);
    os << std::endl << "<<<<<<<<<<ParseTree<<<<<<<<<<";
    return os;
}

void ParseTree::printTree(ParseTreeNode *node, std::ostream &fmt, std::string &indent) const {
    if (node == nullptr) {
        fmt << indent << "null";
        return;
    }
    fmt << indent << node->getNodeName();
    if (node->childNum() == 0) {
        return;
    }
    fmt << "(" << std::endl;
    indent.push_back('\t');
    for (int i = 0; i < node->childNum(); ++i) {
        printTree(node->getChild(i), fmt, indent);
        if (i + 1 < node->childNum()) {
            fmt << ",";
        }
        fmt << std::endl;
    }
    indent.pop_back();
    fmt << indent << ")";
}

ParseTree::~ParseTree() {
    delete root;
    root = nullptr;
}

