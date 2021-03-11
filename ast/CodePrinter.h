//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_CODEPRINTER_H
#define DESIGN_1_CODEPRINTER_H

#include "ASTNode.h"

/**
 * 直接输出代码的叶子节点，抽象类
 */
class CodePrinter : public ASTLeaf{
public:
    explicit CodePrinter();
    void genCode(IoUtil &ioUtil) override;
};


#endif //DESIGN_1_CODEPRINTER_H
