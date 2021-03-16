//
// Created by laugh on 2021/3/16.
//

#ifndef DESIGN_1_ORIGINPRINTFUNCNODE_H
#define DESIGN_1_ORIGINPRINTFUNCNODE_H

#include "OriginBaseFuncDefineNode.h"
#include "OriginStringNode.h"

class OriginPrintFuncNode : public OriginBaseFuncDefineNode{
public:
    void genCode(IoUtil &ioUtil) override;
    std::string toString() const override;
    std::string getHashMsg() override;
};

Object *printStr(Object *obj) {
    auto str = dynamic_cast<String *>(obj);
    if (str == nullptr) {
        return nullptr;
    }
    std::cout << str->getString();
    return nullptr;
}


#endif //DESIGN_1_ORIGINPRINTFUNCNODE_H
