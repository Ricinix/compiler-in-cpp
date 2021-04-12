//
// Created by laugh on 2021/3/16.
//

#ifndef DESIGN_1_ORIGINARRAYNODE_H
#define DESIGN_1_ORIGINARRAYNODE_H

#include "OriginObjectNode.h"
#include "OriginStringNode.h"
#include "OriginNumberNode.h"
#include <map>
#include <sstream>
#include <initializer_list>

class OriginArrayNode : public OriginBaseObjDefineNode {
public:
    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;
};

class Array : public Object {
private:
    std::map<std::string, Object *> container;
public:
    static Array *newObj() {
        return new Array();
    }
    static Array *newObj(std::initializer_list<Object*> objArr) {
        auto *arr = new Array();
        int i = 0;
        for (auto &obj : objArr){
            arr->container[std::to_string(i++)] = obj;
        }
        return arr;
    }

    Object *at(Object *obj) override {
        auto *str = dynamic_cast<String *>(obj->toString());
        if (str == nullptr) {
            return nullptr;
        }
        return container.find(str->getString())->second;
    }

    Object *removeAt(Object *obj) override {
        auto *str = dynamic_cast<String *>(obj->toString());
        if (str == nullptr) {
            return nullptr;
        }
        auto iter = container.find(str->getString());
        if (iter != container.cend()) {
            container.erase(iter);
            return True::newObj();
        }
        return nullptr;
    }

    Object *insert(Object *index, Object *obj) override {
        auto *str = dynamic_cast<String *>(index->toString());
        if (str == nullptr) {
            return nullptr;
        }
        container[str->getString()] = obj;
        return obj;
    }

    Object *clear() override {
        container.clear();
        return nullptr;
    }

    Object *size() override {
        return Number::newObj((int)container.size());
    }

    Object *toString() override {
        std::ostringstream fmt;
        fmt << "[";
        int i = 0;
        for (auto &element : container) {
            auto *str = dynamic_cast<String *>(element.second->toString());
            if (str != nullptr) {
                fmt << str->getString();
            }
            if (++i != container.size()) {
                fmt << ", ";
            }
        }
        fmt << "]";
        return String::newObj(fmt.str());
    }
};


#endif //DESIGN_1_ORIGINARRAYNODE_H
