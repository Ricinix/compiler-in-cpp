//
// Created by laugh on 2021/3/2.
//

#include "AbstractSyntaxTree.h"
#include "OpNodeImport.h"
#include "OriginNumberNode.h"
#include "OriginArrayNode.h"
#include "OriginPrintFuncNode.h"
#include "../domain/exception.h"
#include "../rule/SymbolTable.h"
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

void AbstractSyntaxTree::printTree(ASTNode *node, std::ostream &fmt, std::string &indent) const {
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

void AbstractSyntaxTree::generateCppCode(IoUtil &ioUtil) {
    initObject();
    checkFunc(root);
    getRoot()->genCode(ioUtil);
}

void AbstractSyntaxTree::translateToCppTree(AbstractSyntaxTree::ASTHelper *helper) {
    solveImport(helper);
}

void AbstractSyntaxTree::solveImport(AbstractSyntaxTree::ASTHelper *helper) {
    std::vector<OpNodeImport *> importNodeList;
    for (int i = 0; i < getRootInProgram()->stmtNum(); ++i) {
        auto *stmt = getRootInProgram()->getStmt(i);
        if (stmt->numChildren() > 0 && stmt->child(0)->getType() == ASTNodeType::importNode) {
            auto *import = dynamic_cast<OpNodeImport *>(stmt->child(0));
            if (import != nullptr) {
                importNodeList.push_back(import);
            }
        }
    }
    for (auto &import : importNodeList) {
        auto *ast = helper->loadModule(import->getPathInStr());
        if (ast != nullptr) {
            concat(ast);
            delete ast;
        }
        // 然后销毁当前import结点
        getRoot()->removeAndDelete(import->getFather());
    }
}

void AbstractSyntaxTree::initObject() {
    if (originObj != nullptr || getRoot() == nullptr) {
        return;
    }
    originObj = new OriginObjectNode();
    getRootInProgram()->insertDefineNode(0, new OriginPrintFuncNode);
    getRootInProgram()->insertDefineNode(0, new OriginArrayNode);
    getRootInProgram()->insertDefineNode(0, new OriginNumberNode);
    getRootInProgram()->insertDefineNode(0, new OriginStringNode);
    getRootInProgram()->insertDefineNode(0, new OriginTrueNode);
    getRootInProgram()->insertDefineNode(0, originObj);
}

void AbstractSyntaxTree::checkFunc(ASTNode *node) {
    if (node->getType() == ASTNodeType::method) {
        auto *m = dynamic_cast<DecorateNodeMethod *>(node);
        if (m == nullptr) {
            throw ParseException("checkFunc m is nullptr");
        }
        if (m->isStaticMethod()) {
            SymbolTable::addStaticMethod(m->getStaticHashMsg());
        } else {
            originObj->addVirtualMethod(m);
        }
        return;
    }
    for (int i = 0; i < node->numChildren(); ++i) {
        checkFunc(node->child(i));
    }
}

OpNodeProgram *AbstractSyntaxTree::getRootInProgram() {
    if (programRoot != nullptr) {
        return programRoot;
    }
    if (getRoot()->getType() == ASTNodeType::program) {
        auto *program = dynamic_cast<OpNodeProgram *>(getRoot());
        programRoot = program;
        if (programRoot == nullptr) {
            throw ParseException("ast root is not program node");
        }
        return programRoot;
    }
    return nullptr;
}

void AbstractSyntaxTree::concat(AbstractSyntaxTree *ast) {
    for (int i = 0; i < ast->getRoot()->numChildren(); ++i) {
        auto *child = ast->getRoot()->child(i);
        getRootInProgram()->addNode(child);
    }
    ast->getRoot()->clear();
}

AbstractSyntaxTree::ASTHelper::ASTHelper(const std::string &inPath, AbstractSyntaxTree *(*loadFunc)(const std::string &)) {
    originPath = inPath;
    load = loadFunc;
}

AbstractSyntaxTree *AbstractSyntaxTree::ASTHelper::loadModule(const std::string &path) {
    std::string targetPath = originPath;
    int index = targetPath.find_last_of('/');
    targetPath = targetPath.replace(index, targetPath.size() - index, "/" + path);
    if (!SymbolTable::addModule(targetPath)) {
        return nullptr;
    }
    return load(targetPath);
}
