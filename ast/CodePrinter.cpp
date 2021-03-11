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
