//
// Created by laugh on 2021/3/2.
//

#ifndef DESIGN_1_SYMBOLTABLE_H
#define DESIGN_1_SYMBOLTABLE_H

#include <map>
#include <vector>

class TableCell {
private:
    std::vector<std::string> idList;
public:
    TableCell *next = nullptr;
    TableCell *prior = nullptr;
    bool exist(const std::string &id);
    void add(const std::string &id);
};

class SymbolTable {
private:
    static std::map<std::string, bool> reservedWordMap;
    static TableCell *tail;
    static void initReservedWordMap();
public:
    static bool isReservedWord(const std::string &word);
    static void addReservedWord(const std::string &word);
    static bool insert(const std::string &id);
    static void newCell();
    static void popCell();
};


#endif //DESIGN_1_SYMBOLTABLE_H
