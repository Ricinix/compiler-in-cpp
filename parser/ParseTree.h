//
// Created by laugh on 2021/3/1.
//

#ifndef DESIGN_1_PARSETREE_H
#define DESIGN_1_PARSETREE_H

#include "ParseTreeNode.h"

class ParseTree {
private:
    ParseTreeNode* root = nullptr;
public:
    ParseTreeNode* getRoot();
    void setRoot(ParseTreeNode* node);
};


#endif //DESIGN_1_PARSETREE_H
