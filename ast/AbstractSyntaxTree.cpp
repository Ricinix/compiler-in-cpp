//
// Created by laugh on 2021/3/2.
//

#include "AbstractSyntaxTree.h"

AbstractSyntaxTree::AbstractSyntaxTree(ParseTree *parseTree) {

}

void AbstractSyntaxTree::translateToAst(ParseTreeNode *ptNode, ASTNode *astNode) {

}

void AbstractSyntaxTree::eval() {
    root->work(nullptr, nullptr);
}
