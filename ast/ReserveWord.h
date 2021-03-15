//
// Created by laugh on 2021/3/15.
//

#ifndef DESIGN_1_RESERVEWORD_H
#define DESIGN_1_RESERVEWORD_H

#include "ASTNode.h"

class ReserveWord : public ASTLeaf {
public:
    explicit ReserveWord(Token *token_ptr);
    void genCode(IoUtil &ioUtil) override;
};


#endif //DESIGN_1_RESERVEWORD_H
