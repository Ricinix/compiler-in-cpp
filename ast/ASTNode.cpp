//
// Created by laugh on 2020/12/24.
//

#include <sstream>
#include "ASTNode.h"
#include "../domain/exception.h"

ASTNode *ASTNode::child(int i) {
    return nullptr;
}

int ASTNode::numChildren() const {
    return 0;
}

std::string ASTNode::location() const {
    return "";
}


std::string ASTNode::toString() const {
    return "";
}

std::unique_ptr<ASTNode> ASTNode::work() {
    return nullptr;
}

void ASTNode::genCode(IoUtil &ioUtil) {

}

void ASTNode::setFather(ASTNode* node) {
    father = node;
}

ASTNode *ASTNode::getFather() {
    return father;
}

void ASTNode::insert(int i, ASTNode *node) {
    throw IndexOutOfBoundsException(i);
}

void ASTNode::remove(int i) {
    throw IndexOutOfBoundsException(i);
}

void ASTNode::remove(ASTNode* node) {
    throw IndexOutOfBoundsException(0);
}

void ASTNode::append(ASTNode *node) {
    throw IndexOutOfBoundsException(0);
}

ASTNodeType ASTNode::getType() {
    return ASTNodeType::empty;
}

ASTLeaf::ASTLeaf(Token *token_p) {
    token_ptr = token_p;
}

ASTNode *ASTLeaf::child(int i) {
    throw IndexOutOfBoundsException(i);
}

int ASTLeaf::numChildren() const {
    return ASTNode::numChildren();
}

std::string ASTLeaf::location() const {
    std::ostringstream fmt;
    fmt << "at line " << token_ptr->getLineNumber();
    return fmt.str();
}

Token *ASTLeaf::token() {
    return token_ptr;
}

std::ostream &operator<<(std::ostream &os, const ASTLeaf &astLeaf) {
    os << ">>>>>>>>>>ASTLeaf>>>>>>>>>>" << std::endl;
    os << *astLeaf.token_ptr << std::endl;
    os << "<<<<<<<<<<ASTLeaf<<<<<<<<<<";
    return os;
}

std::string ASTLeaf::toString() const {
    return token_ptr->getText();
}

std::unique_ptr<ASTNode> ASTLeaf::work() {
    return ASTNode::work();
}

void ASTLeaf::genCode(IoUtil &ioUtil) {
    ASTNode::genCode(ioUtil);
}

ASTNodeType ASTLeaf::getType() {
    return ASTNode::getType();
}

ASTList::ASTList(const std::vector<ASTNode *> &v) {
    children = v;
    for (auto &child : children) {
        child->setFather(this);
    }
}

ASTNode *ASTList::child(int i) {
    return children[i];
}

int ASTList::numChildren() const {
    return children.size();
}

std::string ASTList::location() const {
    for (auto &t : children) {
        std::string s = t->location();
        if (!s.empty()) {
            return s;
        }
    }
    return "";
}

std::ostream &operator<<(std::ostream &os, const ASTList &astList) {
    os << ">>>>>>>>>>ASTList>>>>>>>>>>" << std::endl;
    os << "children: " << astList.toString() << std::endl;
    os << "<<<<<<<<<<ASTList<<<<<<<<<<";
    return os;
}

std::string ASTList::toString() const {
    return "AST List";
}

ASTList::~ASTList() {
    for (auto &node_ptr : children) {
        delete node_ptr;
    }
    children.clear();
}

std::unique_ptr<ASTNode> ASTList::work() {
    return ASTNode::work();
}

void ASTList::genCode(IoUtil &ioUtil) {
    ASTNode::genCode(ioUtil);
}

void ASTList::addChild(ASTNode *node) {
    if (node == nullptr) {
        return;
    }
    children.push_back(node);
    node->setFather(this);
}

void ASTList::insert(int i, ASTNode *node) {
    children.insert(children.cbegin() + i, node);
    node->setFather(this);
}

void ASTList::remove(int i) {
    auto *node = children[i];
    children.erase(children.cbegin() + i, children.cbegin() + i + 1);
    delete node;
}

void ASTList::remove(ASTNode *node) {
    for (int i = 0; i < children.size(); ++i) {
        if (children[i] == node) {
            remove(i);
            break;
        }
    }
}

void ASTList::append(ASTNode *node) {
    children.push_back(node);
    node->setFather(this);
}

ASTNodeType ASTList::getType() {
    return ASTNode::getType();
}
