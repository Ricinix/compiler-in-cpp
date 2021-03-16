//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_CODEPRINTER_H
#define DESIGN_1_CODEPRINTER_H

#include "DefineNodeDomain.h"
#include "DecorateNodeMethod.h"
#include "../domain/exception.h"

/**
 * 直接输出代码的叶子节点，抽象类
 */
class CodePrinter : public ASTLeaf {
public:
    explicit CodePrinter();

    void genCode(IoUtil &ioUtil) override;

    std::string location() const override;

    std::string toString() const override;

    friend std::ostream &operator<<(std::ostream &os, const CodePrinter &astLeaf);

    ASTNodeType getType() override;
};

class MethodCodePrinter : public DecorateNodeMethod {
public:
    MethodCodePrinter();
    void genCode(IoUtil &ioUtil) override;
    std::string toString() const override;
    std::string getHashMsg() const override;
};

class OriginNodePublicMethod : public MethodCodePrinter {
private:
    std::string block;
public:
    explicit OriginNodePublicMethod(const std::string &content);
    void genCode(IoUtil &ioUtil) override;
};

class OriginNodeVirtualMethod : public MethodCodePrinter {
private:
    std::string methodName;
    int paramNum;
public:
    OriginNodeVirtualMethod(const std::string &name, int paramCount);
    explicit OriginNodeVirtualMethod(DecorateNodeMethod *node);
    void genCode(IoUtil &ioUtil) override;
    std::string getHashMsg() const override;
};






#endif //DESIGN_1_CODEPRINTER_H
