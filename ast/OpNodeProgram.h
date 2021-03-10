//
// Created by laugh on 2021/3/3.
//

#ifndef DESIGN_1_OPNODEPROGRAM_H
#define DESIGN_1_OPNODEPROGRAM_H

#include "ASTNode.h"

/**
 * 连续执行多个独立语句
 */
class OpNodeProgram : public ASTList {
private:
    explicit OpNodeProgram(const std::vector<ASTNode *> &v);
public:
    void genCode(IoUtil &ioUtil) override;

    class Builder {
    private:
        std::vector<ASTNode *> programSet;
    public:
        void appendChild(ASTNode* node);
        OpNodeProgram* build();
    };
};


#endif //DESIGN_1_OPNODEPROGRAM_H
