//
// Created by laugh on 2020/12/29.
//

#include "NumberLiteral.h"

NumberLiteral::NumberLiteral(Token *token_ptr) : ASTLeaf(token_ptr) {
    decimalsToken = nullptr;
}

void NumberLiteral::genCode(IoUtil &ioUtil) {
    ioUtil.appendContent("Number::newObj(");
    ioUtil.appendContent(token_ptr->getText());
    if (decimalsToken != nullptr) {
        ioUtil.appendContent(".")
                .appendContent(decimalsToken->getText());
    }
    ioUtil.appendContent(")");
    ioUtil.appendContent(" ");
}

NumberLiteral::NumberLiteral(Token *integer, Token *decimals) : ASTLeaf(integer) {
    decimalsToken = decimals;
}

ASTNodeType NumberLiteral::getType() {
    return ASTNodeType::number;
}
