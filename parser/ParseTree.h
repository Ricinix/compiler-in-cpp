//
// Created by laugh on 2021/3/1.
//

#ifndef DESIGN_1_PARSETREE_H
#define DESIGN_1_PARSETREE_H

#include "ParseTreeNode.h"
#include <sstream>

class ParseTree {
private:
    ParseTreeNode* root = nullptr;
    void printTree(ParseTreeNode *node, std::ostream &fmt, std::string &indent) const;
public:
    ParseTreeNode* getRoot();
    void setRoot(ParseTreeNode* node);
    friend std::ostream &operator<<(std::ostream &os, const ParseTree &tree);
};


#endif //DESIGN_1_PARSETREE_H
