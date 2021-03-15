//
// Created by laugh on 2021/3/15.
//

#include "OriginStringNode.h"
#include "CodePrinter.h"

void OriginStringNode::init() {
    addDomain(new OriginNodePrivateDomain("std::string s;"));
    addMethod(new OriginNodePublicMethod(
            "explicit String(const std::string &str) {\n"
            "        s = str;\n"
            "    }\n"
    ));
    addMethod(new OriginNodePublicMethod(
            "std::string getString() {\n"
            "        return s;\n"
            "    }\n"
    ));
    addMethod(new OriginNodePublicMethod(
            "static String *newObj() {\n"
            "        return new String(\"\");\n"
            "    }\n"
    ));
    addMethod(new OriginNodePublicMethod(
            "static String *newObj(const std::string &str) {\n"
            "        return new String(str);\n"
            "    }\n"
    ));
    addMethod(new OriginNodePublicMethod(
            "Object * plus(Object *obj) override {\n"
            "        auto str = dynamic_cast<String *>(obj);\n"
            "        if (str == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        return String::newObj(s + str->getString());\n"
            "    }\n"
    ));
    addMethod(new OriginNodePublicMethod(
            "Object * lessThan(Object *obj) override {\n"
            "        auto str = dynamic_cast<String *>(obj);\n"
            "        if (str == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        return s < str->getString() ? True::newObj() : nullptr;\n"
            "    }\n"
    ));
    addMethod(new OriginNodePublicMethod(
            "Object * lessEqualThan(Object *obj) override {\n"
            "        auto str = dynamic_cast<String *>(obj);\n"
            "        if (str == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        return s <= str->getString() ? True::newObj() : nullptr;\n"
            "    }\n"
    ));
    addMethod(new OriginNodePublicMethod(
            "Object * moreThan(Object *obj) override {\n"
            "        auto str = dynamic_cast<String *>(obj);\n"
            "        if (str == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        return s > str->getString() ? True::newObj() : nullptr;\n"
            "    }\n"
    ));
    addMethod(new OriginNodePublicMethod(
            "Object * moreEqualThan(Object *obj) override {\n"
            "        auto str = dynamic_cast<String *>(obj);\n"
            "        if (str == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        return s >= str->getString() ? True::newObj() : nullptr;\n"
            "    }\n"
    ));
    addMethod(new OriginNodePublicMethod(
            "Object * equal(Object *obj) override {\n"
            "        auto str = dynamic_cast<String *>(obj);\n"
            "        if (str == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        return s == str->getString() ? True::newObj() : nullptr;\n"
            "    }\n"
    ));
}

void OriginStringNode::genCode(IoUtil &ioUtil) {
    if (!isInit) {
        init();
        isInit = true;
    }
    ioUtil.appendContent("class String : public Object {\n");
    for (auto &domain : domainSet) {
        domain->genCode(ioUtil);
    }
    for (auto &method : methodSet) {
        method->genCode(ioUtil);
    }
    ioUtil.appendContent("}\n");
}
