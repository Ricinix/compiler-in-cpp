//
// Created by laugh on 2021/3/2.
//

#include "SymbolTable.h"

std::map<std::string, ReservedWord*> SymbolTable::reservedWordMap;

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
    reservedWordMap["{"] = new ReservedWord();
    reservedWordMap["}"] = new ReservedWord();
    reservedWordMap["while"] = new ReservedWord();
    reservedWordMap["if"] = new ReservedWord();
    reservedWordMap[";"] = new ReservedWord();
}
