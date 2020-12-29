//
// Created by laugh on 2020/12/29.
//

#include "Name.h"

Name::Name(Token *token_ptr) : ASTLeaf(token_ptr) {

}

std::string Name::name() const {
    return token_ptr->getText();
}
