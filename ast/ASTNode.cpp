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

ASTList::ASTList(const std::vector<ASTNode *> &v) {
    children = v;
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
    std::ostringstream fmt("(");
    std::string sep;
    for (auto &t : children) {
        fmt << sep;
        sep = " ";
        fmt << t->toString();
    }
    return fmt.str();
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
