//
// Created by laugh on 2021/3/11.
//

#include "StringLiteral.h"

StringLiteral::StringLiteral(Token *t) : ASTLeaf(t) {

}

void StringLiteral::genCode(IoUtil &ioUtil) {
    ioUtil.appendContent("String::newObj(\"")
    .appendContent(token_ptr->getText())
    .appendContent("\")");
}

std::string StringLiteral::toString() const {
    return token_ptr->getText();
}
