//
// Created by laugh on 2021/3/3.
//

#include "ProgramOpNode.h"

std::unique_ptr<ASTNode> ProgramOpNode::work() {
    for (auto &child : children) {
        child->work();
    }
    return nullptr;
}
