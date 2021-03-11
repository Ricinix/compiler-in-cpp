//
// Created by laugh on 2021/3/2.
//

#include "AbstractSyntaxTree.h"

AbstractSyntaxTree::AbstractSyntaxTree(ASTNode *rootNode) {
    root = rootNode;
}

ASTNode *AbstractSyntaxTree::getRoot() {
    return root;
}
