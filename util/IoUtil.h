//
// Created by laugh on 2020/12/11.
//

#ifndef DESIGN_1_IOUTIL_H
#define DESIGN_1_IOUTIL_H

#include <string>
#include <iostream>
#include <fstream>
#include "Log.h"

class IoUtil {

private:
    std::ifstream fileIn;
    std::ofstream fileOut;
    std::string inPath;
    std::string outPath;
    int lineNo;

    void checkInit();

public:
    char getNext();

    std::string readLine();

    int getLineNumber() const;

    void appendContent(const std::string &content);

    void newLine();

    explicit IoUtil(const std::string &val_path);

    IoUtil(const std::string &srcPath, const std::string &targetPath);

    IoUtil(const IoUtil &old_ioUtil);

    IoUtil(IoUtil &&old_ioUtil) noexcept;

    ~IoUtil();

    IoUtil &operator=(const IoUtil &old_ioUtil);

    friend std::ostream &operator<<(std::ostream &os, const IoUtil &ioUtil);

};


#endif //DESIGN_1_IOUTIL_H
