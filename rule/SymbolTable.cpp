//
// Created by laugh on 2021/3/2.
//

#include "../util/Log.h"
#include "SymbolTable.h"
#include <algorithm>

std::map<std::string, bool> SymbolTable::reservedWordMap;
TableCell *SymbolTable::tail = new TableCell;
std::vector<std::string> SymbolTable::modulePathList;

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

void SymbolTable::newCell() {
    tail->next = new TableCell;
    tail->next->prior = tail;
    tail = tail->next;
}

void SymbolTable::popCell() {
    tail = tail->prior;
    delete tail->next;
    tail->next = nullptr;
}

bool SymbolTable::insert(const std::string &id) {
    auto *cell = tail;
    while (cell != nullptr) {
        if (cell->exist(id)) {
            return false;
        }
        cell = cell->prior;
    }
    tail->add(id);
    return true;
}

bool SymbolTable::addModule(const std::string &path) {
    std::string modulePath = formatPath(path);
    if (std::find(modulePathList.cbegin(), modulePathList.cend(), modulePath) != modulePathList.end()) {
        return false;
    }
    modulePathList.push_back(modulePath);
    Log::info("record module: " + modulePath);
    return true;
}

std::string SymbolTable::formatPath(const std::string &path) {
    int dotDotIndex;
    std::string modulePath = path;
    dotDotIndex = modulePath.find("..");
    while (dotDotIndex != std::string::npos) {
        int startIndex = dotDotIndex;
        int backslashCount = 0;
        while (startIndex > 0) {
            if (modulePath[startIndex] == '/') {
                ++backslashCount;
                if (backslashCount == 2) {
                    break;
                }
            }
            --startIndex;
        }
        modulePath = modulePath.replace(startIndex, dotDotIndex + 3 - startIndex, "");
        dotDotIndex = modulePath.find("..");
    }
    return modulePath;
}

bool TableCell::exist(const std::string &id) {
    return std::find(idList.cbegin(), idList.cend(), id) != idList.end();
}

void TableCell::add(const std::string &id) {
    idList.push_back(id);
}
