//
// Created by laugh on 2021/3/11.
//

#include "CodePrinter.h"

CodePrinter::CodePrinter() : ASTLeaf(nullptr) {

}

void CodePrinter::genCode(IoUtil &ioUtil) {
    ASTLeaf::genCode(ioUtil);
}

std::string CodePrinter::toString() const {
    return "CodePrinter";
}

std::string CodePrinter::location() const {
    return "";
}

std::ostream &operator<<(std::ostream &os, const CodePrinter &astLeaf) {
    os << ">>>>>>>>>>ASTLeaf>>>>>>>>>>" << std::endl;
    os << astLeaf.toString() << std::endl;
    os << "<<<<<<<<<<ASTLeaf<<<<<<<<<<";
    return os;
}

ASTNodeType CodePrinter::getType() {
    return ASTNodeType::codePrinter;
}

MethodCodePrinter::MethodCodePrinter() : DecorateNodeMethod(nullptr, false) {

}

std::string MethodCodePrinter::toString() const {
    return "MethodCodePrinter";
}

void MethodCodePrinter::genCode(IoUtil &ioUtil) {
    DecorateNodeMethod::genCode(ioUtil);
}

std::string MethodCodePrinter::getHashMsg() const {
    return DecorateNodeMethod::getHashMsg();
}

OriginNodePublicMethod::OriginNodePublicMethod(const std::string &content) {
    block = content;
}

void OriginNodePublicMethod::genCode(IoUtil &ioUtil) {
    ioUtil.appendContent("public:");
    ioUtil.newLine();
    ioUtil.appendContent(block);
    ioUtil.newLine();
}

std::string OriginNodeVirtualMethod::getHashMsg() const {
    return methodName + "_" + std::to_string(paramNum);
}

OriginNodeVirtualMethod::OriginNodeVirtualMethod(const std::string &name, int paramCount) {
    methodName = name;
    paramNum = paramCount;
}

void OriginNodeVirtualMethod::genCode(IoUtil &ioUtil) {
    if (methodName.empty()) {
        return;
    }
    ioUtil.appendContent("virtual Object *");
    ioUtil.appendContent(methodName);
    ioUtil.appendContent("(");
    for (int i = 0; i < paramNum; ++i) {
        ioUtil.appendContent("Object *arg" + std::to_string(i + 1));
        if (i != paramNum - 1) {
            ioUtil.appendContent(", ");
        }
    }
    ioUtil.appendContent(") { return nullptr; }\n");
}

OriginNodeVirtualMethod::OriginNodeVirtualMethod(DecorateNodeMethod *node) {
    if (node == nullptr) {
        paramNum = 0;
    } else {
        paramNum = node->getParamNum();
        methodName = node->getMethodName();
    }
}
