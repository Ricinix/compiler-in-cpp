//
// Created by laugh on 2021/3/2.
//

#ifndef DESIGN_1_ABSTRACTSYNTAXTREE_H
#define DESIGN_1_ABSTRACTSYNTAXTREE_H

#include "ASTNode.h"
#include "OriginObjectNode.h"
#include <sstream>

class AbstractSyntaxTree {
private:
    ASTNode *root = nullptr;

    OriginObjectNode *originObj = nullptr;

    void printTree(ASTNode *node, std::ostream &fmt, std::string &indent) const;

    void initObject();

    void solveImport(AbstractSyntaxTree *(*load)(const std::string &));

    void checkFunc(ASTNode *node);
public:
    class ASTHelper {
    public:
        AbstractSyntaxTree *(*load)(const std::string &);
    };

    explicit AbstractSyntaxTree(ASTNode *rootNode);

    ~AbstractSyntaxTree();

    ASTNode *getRoot();

    void translateToCppTree(AbstractSyntaxTree::ASTHelper *helper);

    friend std::ostream &operator<<(std::ostream &os, const AbstractSyntaxTree &tree);

    void generateCppCode(IoUtil &ioUtil);

};



#endif //DESIGN_1_ABSTRACTSYNTAXTREE_H
