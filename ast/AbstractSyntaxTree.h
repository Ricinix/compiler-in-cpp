//
// Created by laugh on 2021/3/2.
//

#ifndef DESIGN_1_ABSTRACTSYNTAXTREE_H
#define DESIGN_1_ABSTRACTSYNTAXTREE_H

#include "ASTNode.h"
#include <sstream>

class AbstractSyntaxTree {
private:
    ASTNode *root;

    void printTree(ASTNode *node, std::ostream &fmt, std::string &indent) const;
public:
    explicit AbstractSyntaxTree(ASTNode *rootNode);

    ~AbstractSyntaxTree();

    ASTNode* getRoot();

    void translateToCppTree();

    friend std::ostream &operator<<(std::ostream &os, const AbstractSyntaxTree &tree);

};


#endif //DESIGN_1_ABSTRACTSYNTAXTREE_H
