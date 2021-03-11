//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_STRINGLITERAL_H
#define DESIGN_1_STRINGLITERAL_H

#include "ASTNode.h"

class StringLiteral : public ASTLeaf {
public:
    explicit StringLiteral(Token* t);
    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;
};


#endif //DESIGN_1_STRINGLITERAL_H
