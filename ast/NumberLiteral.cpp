//
// Created by laugh on 2020/12/29.
//

#include "NumberLiteral.h"

NumberLiteral::NumberLiteral(Token *token_ptr) : ASTLeaf(token_ptr) {
    decimalsToken = nullptr;
}

void NumberLiteral::genCode(IoUtil &ioUtil) {
    ioUtil.appendContent(token_ptr->getText() + " ");
}

NumberLiteral::NumberLiteral(Token *integer, Token *decimals) : ASTLeaf(integer) {
    decimalsToken = decimals;
}
