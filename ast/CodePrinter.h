//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_CODEPRINTER_H
#define DESIGN_1_CODEPRINTER_H

#include "DecorateNodeMethod.h"
#include "../domain/exception.h"

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
