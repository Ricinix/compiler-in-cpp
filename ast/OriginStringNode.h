//
// Created by laugh on 2021/3/15.
//

#ifndef DESIGN_1_ORIGINSTRINGNODE_H
#define DESIGN_1_ORIGINSTRINGNODE_H

#include "OriginObjectNode.h"

class OriginStringNode : public OriginBaseObjDefineNode {
public:
    void genCode(IoUtil &ioUtil) override;
    std::string toString() const override;
};

class String : public Object {
private:
    std::string s;
public:
    explicit String(const std::string &str) {
        s = str;
    }
    std::string getString() {
        return s;
    }
    static String *newObj() {
        return new String("");
    }
    static String *newObj(const std::string &str) {
        return new String(str);
    }
    Object * plus(Object *obj) override {
        auto str = dynamic_cast<String *>(obj);
        if (str == nullptr) {
            return nullptr;
        }
        return String::newObj(s + str->getString());
    }
    Object * lessThan(Object *obj) override {
        auto str = dynamic_cast<String *>(obj);
        if (str == nullptr) {
            return nullptr;
        }
        return s < str->getString() ? True::newObj() : nullptr;
    }
    Object * lessEqualThan(Object *obj) override {
        auto str = dynamic_cast<String *>(obj);
        if (str == nullptr) {
            return nullptr;
        }
        return s <= str->getString() ? True::newObj() : nullptr;
    }
    Object * moreThan(Object *obj) override {
        auto str = dynamic_cast<String *>(obj);
        if (str == nullptr) {
            return nullptr;
        }
        return s > str->getString() ? True::newObj() : nullptr;
    }
    Object * moreEqualThan(Object *obj) override {
        auto str = dynamic_cast<String *>(obj);
        if (str == nullptr) {
            return nullptr;
        }
        return s >= str->getString() ? True::newObj() : nullptr;
    }
    Object * equal(Object *obj) override {
        auto str = dynamic_cast<String *>(obj);
        if (str == nullptr) {
            return nullptr;
        }
        return s == str->getString() ? True::newObj() : nullptr;
    }

};


#endif //DESIGN_1_ORIGINSTRINGNODE_H
