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

DomainCodePrinter::DomainCodePrinter() : DefineNodeDomain(nullptr, false) {

}

void DomainCodePrinter::genCode(IoUtil &ioUtil) {
    DefineNodeDomain::genCode(ioUtil);
}

std::string DomainCodePrinter::toString() const {
    return "DomainCodePrinter";
}

OriginNodePrivateDomain::OriginNodePrivateDomain(const std::string &content) {
    stmt = content;
}

void OriginNodePrivateDomain::genCode(IoUtil &ioUtil) {
    ioUtil.appendContent("private:");
    ioUtil.newLine();
    ioUtil.appendContent(stmt);
    ioUtil.newLine();
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

OriginNodePrivateMethod::OriginNodePrivateMethod(const std::string &content) {
    block = content;
}

void OriginNodePrivateMethod::genCode(IoUtil &ioUtil) {
    ioUtil.appendContent("private:");
    ioUtil.newLine();
    ioUtil.appendContent(block);
    ioUtil.newLine();
}

std::string OriginNOdeVirtualMethod::getHashMsg() const {
    return methodName + "_" + std::to_string(paramNum);
}

OriginNOdeVirtualMethod::OriginNOdeVirtualMethod(const std::string &name, int paramCount) {
    methodName = name;
    paramNum = paramCount;
}

void OriginNOdeVirtualMethod::genCode(IoUtil &ioUtil) {
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
    ioUtil.appendContent(") { return nullptr; }");
}

OriginNOdeVirtualMethod::OriginNOdeVirtualMethod(DecorateNodeMethod *node) {
    if (node == nullptr) {
        paramNum = 0;
    } else {
        paramNum = node->getParamNum();
        methodName = node->getMethodName();
    }
}
