//
// Created by laugh on 2021/3/2.
//

#include "SymbolTable.h"

std::map<std::string, Operator*> SymbolTable::reservedWordMap;

/**
 * 不包含Op
 *
 * @param word
 * @return
 */
bool SymbolTable::isReservedWord(const std::string &word) {
    if (reservedWordMap.empty()) {
        initReservedWordMap();
    }
    return reservedWordMap.find(word) != reservedWordMap.end();
}

void SymbolTable::initReservedWordMap() {
    reservedWordMap["{"] = new Operator();
    reservedWordMap["}"] = new Operator();
    reservedWordMap["while"] = new Operator();
    reservedWordMap["if"] = new Operator();
    reservedWordMap[";"] = new Operator();
}
