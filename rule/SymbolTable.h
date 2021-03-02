//
// Created by laugh on 2021/3/2.
//

#ifndef DESIGN_1_SYMBOLTABLE_H
#define DESIGN_1_SYMBOLTABLE_H

#include <map>
#include "ReservedWord.h"

class SymbolTable {
private:
    static void initReservedWordMap();
    static std::map<std::string, ReservedWord *> reservedWordMap;
public:
    static bool isReservedWord(const std::string &word);
};


#endif //DESIGN_1_SYMBOLTABLE_H
