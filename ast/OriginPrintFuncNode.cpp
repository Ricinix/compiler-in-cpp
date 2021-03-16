//
// Created by laugh on 2021/3/16.
//

#include "OriginPrintFuncNode.h"

std::string OriginPrintFuncNode::toString() const {
    return "print";
}

void OriginPrintFuncNode::genCode(IoUtil &ioUtil) {
    ioUtil.appendContent(
            "Object *printStr(Object *obj) {\n"
            "    auto str = dynamic_cast<String *>(obj);\n"
            "    if (str == nullptr) {\n"
            "        return nullptr;\n"
            "    }\n"
            "    std::cout << str->getString();\n"
            "    return nullptr;\n"
            "}\n"
    );
    ioUtil.newLine();
}

std::string OriginPrintFuncNode::getHashMsg() {
    return "print_1";
}
