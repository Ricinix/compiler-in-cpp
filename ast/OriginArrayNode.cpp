//
// Created by laugh on 2021/3/16.
//

#include "OriginArrayNode.h"
#include "CodePrinter.h"

void OriginArrayNode::init() {
    if (isInit) {
        return;
    }
    isInit = true;
    addDomain(new OriginNodePrivateDomain(
            "std::map<std::string, Object *> container;"
    ));
    addMethod(new OriginNodePublicMethod(
            "Object *at(Object *obj) override {\n"
            "        auto *str = dynamic_cast<String *>(obj);\n"
            "        if (str == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        return container.find(str->getString())->second;\n"
            "    }\n"
    ));
    addMethod(new OriginNodePublicMethod(
            "Object *removeAt(Object *obj) override {\n"
            "        auto *str = dynamic_cast<String *>(obj);\n"
            "        if (str == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        auto iter = container.find(str->getString());\n"
            "        if (iter != container.cend()) {\n"
            "            container.erase(iter);\n"
            "            return True::newObj();\n"
            "        }\n"
            "        return nullptr;\n"
            "    }\n"
    ));
    addMethod(new OriginNodePublicMethod(
            "Object * insert(Object *index, Object *obj) override {\n"
            "        auto *str = dynamic_cast<String *>(obj);\n"
            "        if (str == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        container[str->getString()] = obj;\n"
            "        return obj;\n"
            "    }\n"
    ));
    addMethod(new OriginNodePublicMethod(
            "Object * clear() override {\n"
            "        container.clear();\n"
            "        return nullptr;\n"
            "    }\n"
    ));
    addMethod(new OriginNodePublicMethod(
            "Object * toString() override {\n"
            "        std::ostringstream fmt(\"[\");\n"
            "        int i = 0;\n"
            "        for (auto &element : container) {\n"
            "            auto *str = dynamic_cast<String*>(element.second->toString());\n"
            "            if (str != nullptr) {\n"
            "                fmt << str->getString(); \n"
            "            }\n"
            "            i++;\n"
            "            if (i != container.size()) {\n"
            "                fmt << \", \";\n"
            "            }\n"
            "        }\n"
            "        fmt << \"]\";\n"
            "        return String::newObj(fmt.str());\n"
            "    }\n"
    ));
}

void OriginArrayNode::genCode(IoUtil &ioUtil) {
    init();
    ioUtil.appendContent("class Array : public Object {\n");
    for (auto &domain : domainSet) {
        domain->genCode(ioUtil);
    }
    for (auto &method : methodSet) {
        method->genCode(ioUtil);
    }
    ioUtil.appendContent("}\n");
}
