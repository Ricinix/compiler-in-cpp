//
// Created by laugh on 2021/3/2.
//

#ifndef DESIGN_1_ABSTRACTSYNTAXTREE_H
#define DESIGN_1_ABSTRACTSYNTAXTREE_H

#include "ASTNode.h"

class AbstractSyntaxTree {
private:
    ASTNode *root;
public:
    explicit AbstractSyntaxTree(ASTNode *rootNode);

    ASTNode* getRoot();

};


#endif //DESIGN_1_ABSTRACTSYNTAXTREE_H
