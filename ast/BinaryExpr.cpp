//
// Created by laugh on 2020/12/29.
//

#include "BinaryExpr.h"

BinaryExpr::BinaryExpr(std::vector<ASTNode *> &c) : ASTList(c) {

}

ASTNode *BinaryExpr::left() {
    return child(0);
}

ASTNode *BinaryExpr::right() {
    return child(2);
}

std::string BinaryExpr::getOperator() {
    return dynamic_cast<ASTLeaf *>(child(1))->token()->getText();
}
