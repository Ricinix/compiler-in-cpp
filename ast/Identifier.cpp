//
// Created by laugh on 2020/12/29.
//

#include "Identifier.h"

Identifier::Identifier(Token *token_ptr) : ASTLeaf(token_ptr) {

}

void Identifier::genCode(IoUtil &ioUtil) {
    ioUtil.appendContent(token_ptr->getText() + " ");
}

