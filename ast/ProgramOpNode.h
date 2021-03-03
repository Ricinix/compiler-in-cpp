//
// Created by laugh on 2021/3/3.
//

#ifndef DESIGN_1_PROGRAMOPNODE_H
#define DESIGN_1_PROGRAMOPNODE_H

#include "ASTNode.h"

/**
 * 连续执行多个独立语句
 */
class ProgramOpNode : public ASTList {
public:
    std::unique_ptr<ASTNode> work() override;
};


#endif //DESIGN_1_PROGRAMOPNODE_H
