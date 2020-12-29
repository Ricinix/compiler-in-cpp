//
// Created by laugh on 2020/12/29.
//

#include "NumberLiteral.h"

NumberLiteral::NumberLiteral(Token *token_ptr) : ASTLeaf(token_ptr) {

}

int NumberLiteral::value() const {
    return token_ptr->getNumber();
}
