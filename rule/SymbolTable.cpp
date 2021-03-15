//
// Created by laugh on 2021/3/2.
//

#include "SymbolTable.h"
#include "../domain/constant.h"

std::map<std::string, bool> SymbolTable::reservedWordMap;

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
//    reservedWordMap[RW_LEFT_BRACE] = true;
//    reservedWordMap[RW_RIGHT_BRACE] = true;
//    reservedWordMap[RW_LEFT_SQUARE_BRACKET] = true;
//    reservedWordMap[RW_RIGHT_SQUARE_BRACKET] = true;
//    reservedWordMap[RW_LEFT_BRACKET] = true;
//    reservedWordMap[RW_RIGHT_BRACKET] = true;
//    reservedWordMap[RW_WHILE] = true;
//    reservedWordMap[RW_IF] = true;
//    reservedWordMap[RW_ELSE] = true;
//    reservedWordMap[RW_FUNC] = true;
//    reservedWordMap[RW_RETURN] = true;
//    reservedWordMap[RW_NEW] = true;
//    reservedWordMap[RW_SEMICOLON] = true;
//    reservedWordMap[RW_COMMA] = true;
//    reservedWordMap[RW_DOT] = true;
}

void SymbolTable::addReservedWord(const std::string &word) {
    reservedWordMap[word] = true;
}
