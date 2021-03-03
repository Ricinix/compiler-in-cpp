//
// Created by laugh on 2021/3/2.
//

#ifndef DESIGN_1_ABSTRACTSYNTAXTREE_H
#define DESIGN_1_ABSTRACTSYNTAXTREE_H

#include "../parser/ParseTree.h"
#include "ASTNode.h"

class AbstractSyntaxTree {
private:
    ASTNode *root;

    void translateToAst(ParseTreeNode *ptNode, ASTNode *astNode);

public:
    explicit AbstractSyntaxTree(ParseTree *parseTree);

};


#endif //DESIGN_1_ABSTRACTSYNTAXTREE_H
