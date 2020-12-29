//
// Created by laugh on 2020/12/29.
//

#ifndef DESIGN_1_BINARYEXPR_H
#define DESIGN_1_BINARYEXPR_H

#include "ASTNode.h"
#include <vector>

class BinaryExpr : public ASTList {
public:
    explicit BinaryExpr(std::vector<ASTNode *> &c);
    ASTNode* left();
    ASTNode* right();
    std::string getOperator();
};


#endif //DESIGN_1_BINARYEXPR_H
