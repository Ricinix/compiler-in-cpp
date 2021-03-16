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

//Object *printStr(Object *obj) {
//    if (obj == nullptr) {
//        std::cout << "null" << std::endl;
//        return nullptr;
//    }
//    auto str = dynamic_cast<String *>(obj->toString());
//    if (str == nullptr) {
//        std::cout << "null" << std::endl;
//        return nullptr;
//    }
//    std::cout << str->getString() << std::endl;
//    return nullptr;
//}


#endif //DESIGN_1_ORIGINPRINTFUNCNODE_H
