//
// Created by laugh on 2020/12/29.
//

#ifndef DESIGN_1_IDENTIFIER_H
#define DESIGN_1_IDENTIFIER_H

#include "ASTNode.h"
#include "../lexer/Token.h"

class Identifier: public ASTLeaf {
public:
    explicit Identifier(Token* token_ptr);
    void genCode(IoUtil &ioUtil) override;
};


#endif //DESIGN_1_IDENTIFIER_H
