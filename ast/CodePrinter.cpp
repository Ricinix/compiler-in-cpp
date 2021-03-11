//
// Created by laugh on 2021/3/11.
//

#include "CodePrinter.h"

CodePrinter::CodePrinter() : ASTLeaf(nullptr) {

}

void CodePrinter::genCode(IoUtil &ioUtil) {
    ASTLeaf::genCode(ioUtil);
}
