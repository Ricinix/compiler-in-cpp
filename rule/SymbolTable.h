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

    int idNum() const;

    const std::string &getIdByPos(int i) const;
};

class SymbolTable {
private:
    static std::map<std::string, bool> reservedWordMap;
    static std::vector<std::string> modulePathList;
    static TableCell *tail;

    static void initReservedWordMap();

    static std::string formatPath(const std::string &path);

public:
    static bool isReservedWord(const std::string &word);

    static void addReservedWord(const std::string &word);

    static bool insert(const std::string &id);

    static void newCell();

    static void popCell();

    static int getIdNumInTailCell();

    static const std::string &getIdByPos(int i);

    /**
     * 每解析一个module就向这里插入
     * @param path
     * @return 如果已经解析过则返回false，否则true
     */
    static bool addModule(const std::string &path);
};


#endif //DESIGN_1_SYMBOLTABLE_H
