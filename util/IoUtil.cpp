//
// Created by laugh on 2020/12/11.
//

#include "IoUtil.h"
#include "../domain/exception.h"

IoUtil::IoUtil(const std::string &val_path) {
    inPath = val_path;
    lineNo = 0;
    checkInit();
}

void IoUtil::checkInit() {
    fileIn.open(inPath);
    if (!fileIn.is_open()) {
        throw IoException("open src file fail");
    }
    if (!outPath.empty()) {
        fileOut.open(outPath);
        if (!fileOut.is_open()) {
            throw IoException("open target file fail");
        }
    }
}

char IoUtil::getNext() {
    char c;
    fileIn.get(c);
    return c;
}

IoUtil::IoUtil(const IoUtil &old_ioUtil) {
    inPath = old_ioUtil.inPath;
    lineNo = 0;
    checkInit();
}

std::ostream &operator<<(std::ostream &os, const IoUtil &ioUtil) {
    os << ">>>>>>>>>>IoUtil>>>>>>>>>>" << std::endl;
    os << "inPath: " + ioUtil.inPath << std::endl;
    os << "<<<<<<<<<<IoUtil<<<<<<<<<<";
    return os;
}

IoUtil &IoUtil::operator=(const IoUtil &old_ioUtil) {
    inPath = old_ioUtil.inPath;
    checkInit();
    return *this;
}

IoUtil::IoUtil(IoUtil &&old_ioUtil) noexcept {

}

std::string IoUtil::readLine() {
    std::string line;
    std::getline(fileIn, line);
    ++lineNo;
    if (line.empty() && !fileIn.eof()) {
        return readLine();
    }
    return line;
}

int IoUtil::getLineNumber() const {
    return lineNo;
}

IoUtil::IoUtil(const std::string &srcPath, const std::string &targetPath) {
    inPath = srcPath;
    outPath = targetPath;
    lineNo = 0;
    checkInit();
}

IoUtil::~IoUtil() {
    if (fileIn.is_open()) {
        fileIn.close();
        fileIn.clear();
    }
    if (fileOut.is_open()) {
        fileOut.close();
        fileOut.clear();
    }
}

void IoUtil::appendLine(const std::string &content) {
    if (!fileOut.is_open()) {
        throw IoException("open output file fail");
    }
    fileOut << content << std::endl;
}

void IoUtil::appendEmptyLine() {
    appendLine("");
};
