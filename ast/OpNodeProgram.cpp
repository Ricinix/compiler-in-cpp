//
// Created by laugh on 2021/3/3.
//

#include "OpNodeProgram.h"

std::unique_ptr<ASTNode> OpNodeProgram::work() {
    for (auto &child : children) {
        child->work();
    }
    return nullptr;
}
