//
// Created by laugh on 2020/12/11.
//

#include "IoUtil.h"

IoUtil::IoUtil(const std::string &val_path) {
    path = val_path;
}

void IoUtil::checkInit() {
    fileIn.open(path);
    if (fileIn.is_open()) {
        fileIn.close();
        fileIn.clear();
    }
}

char IoUtil::getNext() {
    char c;
    fileIn.get(c);
    return c;
}

IoUtil::IoUtil(const IoUtil &old_ioUtil) {
    path = old_ioUtil.path;
    checkInit();
}

std::ostream &operator<<(std::ostream &os, const IoUtil &ioUtil) {
    os << ">>>>>>>>>>IoUtil>>>>>>>>>>" << std::endl;
    os << "path: " + ioUtil.path << std::endl;
    os << "<<<<<<<<<<IoUtil<<<<<<<<<<";
    return os;
}

IoUtil &IoUtil::operator=(const IoUtil &old_ioUtil) {
    path = old_ioUtil.path;
    checkInit();
    return *this;
}

IoUtil::IoUtil(IoUtil &&old_ioUtil) noexcept {

};
