//
// Created by laugh on 2021/3/11.
//

#include "StringLiteral.h"

StringLiteral::StringLiteral(Token *t) : ASTLeaf(t) {

}

void StringLiteral::genCode(IoUtil &ioUtil) {
    ioUtil.appendContent("\"" + token_ptr->getText() + "\" ");
}
