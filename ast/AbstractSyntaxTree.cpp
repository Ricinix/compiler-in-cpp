//
// Created by laugh on 2021/3/2.
//

#include "AbstractSyntaxTree.h"
#include <iostream>

AbstractSyntaxTree::AbstractSyntaxTree(ASTNode *rootNode) {
    root = rootNode;
}

ASTNode *AbstractSyntaxTree::getRoot() {
    return root;
}

AbstractSyntaxTree::~AbstractSyntaxTree() {
    delete root;
    root = nullptr;
}

std::ostream &operator<<(std::ostream &os, const AbstractSyntaxTree &tree) {
    std::ostringstream fmt;
    std::string intent;
    os << ">>>>>>>>>>AbstractSyntaxTree>>>>>>>>>>" << std::endl;
    tree.printTree(tree.root, os, intent);
    os << std::endl << "<<<<<<<<<<AbstractSyntaxTree<<<<<<<<<<";
    return os;
}

void AbstractSyntaxTree::printTree(ASTNode *node, std::ostream &fmt, std::string &indent) const{
    if (node == nullptr) {
        fmt << indent << "null";
        return;
    }
    fmt << indent << node->toString();
    if (node->numChildren() == 0) {
        return;
    }
    fmt << "(" << std::endl;
    indent.push_back('\t');
    for (int i = 0; i < node->numChildren(); ++i) {
        printTree(node->child(i), fmt, indent);
        if (i + 1 < node->numChildren()) {
            fmt << ",";
        }
        fmt << std::endl;
    }
    indent.pop_back();
    fmt << indent << ")";
}

void AbstractSyntaxTree::translateToCppTree() {

}
