//
// Created by laugh on 2020/12/29.
//

#ifndef DESIGN_1_NUMBERLITERAL_H
#define DESIGN_1_NUMBERLITERAL_H

#include "ASTNode.h"
#include "../lexer/Token.h"

class NumberLiteral: public ASTLeaf {
public:
    explicit NumberLiteral(Token* token_ptr);
    void genCode(IoUtil &ioUtil) override;
};


#endif //DESIGN_1_NUMBERLITERAL_H
