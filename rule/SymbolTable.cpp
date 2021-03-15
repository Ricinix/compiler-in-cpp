//
// Created by laugh on 2021/3/2.
//

#include "SymbolTable.h"
#include "../domain/constant.h"

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
    reservedWordMap[RW_LEFT_BRACE] = new Operator();
    reservedWordMap[RW_RIGHT_BRACE] = new Operator();
    reservedWordMap[RW_LEFT_SQUARE_BRACKET] = new Operator();
    reservedWordMap[RW_RIGHT_SQUARE_BRACKET] = new Operator();
    reservedWordMap[RW_LEFT_BRACKET] = new Operator();
    reservedWordMap[RW_RIGHT_BRACKET] = new Operator();
    reservedWordMap[RW_WHILE] = new Operator();
    reservedWordMap[RW_IF] = new Operator();
    reservedWordMap[RW_ELSE] = new Operator();
    reservedWordMap[RW_FUNC] = new Operator();
    reservedWordMap[RW_RETURN] = new Operator();
    reservedWordMap[RW_NEW] = new Operator();
    reservedWordMap[RW_SEMICOLON] = new Operator();
    reservedWordMap[RW_COMMA] = new Operator();
    reservedWordMap[RW_DOT] = new Operator();
}
