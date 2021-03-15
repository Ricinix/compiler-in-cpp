//
// Created by laugh on 2021/3/15.
//

#include "ReserveWord.h"

ReserveWord::ReserveWord(Token *token_ptr) : ASTLeaf(token_ptr) {
}

void ReserveWord::genCode(IoUtil &ioUtil) {
    ioUtil.appendContent("!!! print reserve word: " + token_ptr->getText());
}
