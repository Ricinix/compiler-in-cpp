//
// Created by laugh on 2020/12/29.
//

#ifndef DESIGN_1_NAME_H
#define DESIGN_1_NAME_H

#include "ASTNode.h"
#include "../lexer/Token.h"

class Name: public ASTLeaf {
    explicit Name(Token* token_ptr);
    std::string name() const;
};


#endif //DESIGN_1_NAME_H
