//
// Created by laugh on 2021/3/2.
//

#ifndef DESIGN_1_ABSTRACTSYNTAXTREE_H
#define DESIGN_1_ABSTRACTSYNTAXTREE_H

#include "ASTNode.h"
#include "OriginObjectNode.h"
#include "OpNodeProgram.h"
#include <sstream>

class AbstractSyntaxTree {
private:
    ASTNode *root = nullptr;

    OpNodeProgram *programRoot = nullptr;

    OriginObjectNode *originObj = nullptr;

    void printTree(ASTNode *node, std::ostream &fmt, std::string &indent) const;

    void initObject();

    void checkFunc(ASTNode *node);

    void concat(AbstractSyntaxTree *ast);
public:
    class ASTHelper {
    private:
        std::string originPath;
        AbstractSyntaxTree *(*load)(const std::string &);
    public:
        ASTHelper(const std::string &inPath, AbstractSyntaxTree *(*loadFunc)(const std::string &));
        AbstractSyntaxTree *loadModule(const std::string &path);
    };

    explicit AbstractSyntaxTree(ASTNode *rootNode);

    ~AbstractSyntaxTree();

    ASTNode *getRoot();

    OpNodeProgram *getRootInProgram();

    void translateToCppTree(AbstractSyntaxTree::ASTHelper *helper);

    friend std::ostream &operator<<(std::ostream &os, const AbstractSyntaxTree &tree);

    void generateCppCode(IoUtil &ioUtil);

private:
    void solveImport(AbstractSyntaxTree::ASTHelper *helper);

};



#endif //DESIGN_1_ABSTRACTSYNTAXTREE_H
