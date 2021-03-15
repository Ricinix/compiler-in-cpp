//
// Created by laugh on 2021/3/15.
//

#include "OriginNumberNode.h"
#include "CodePrinter.h"

void OriginNumberNode::genCode(IoUtil &ioUtil) {
    if (!isInit) {
        init();
        isInit = true;
    }
    ioUtil.appendContent("class Number : public Object {\n");
    for (auto &domain : domainSet) {
        domain->genCode(ioUtil);
    }
    for (auto &method : methodSet) {
        method->genCode(ioUtil);
    }
    ioUtil.appendContent("}\n");
}

void OriginNumberNode::init() {
    addDomain(new OriginNodePrivateDomain("int _integer = 0;"));
    addDomain(new OriginNodePrivateDomain("double _number = 0;"));
    addDomain(new OriginNodePrivateDomain("bool _isInteger = true;"));
    addMethod(new OriginNodePrivateMethod(
            "bool _isInt() {\n"
            "        return _isInteger;\n"
            "    }\n"
    ));
    // 两种构造器
    addMethod(new OriginNodePublicMethod(
            "explicit Number(int n) {\n"
            "        _integer = n;\n"
            "    }\n"
    ));
    addMethod(new OriginNodePublicMethod(
            "explicit Number(double n) {\n"
            "        _number = n;\n"
            "        _isInteger = false;\n"
            "    }\n"
    ));
    addMethod(new OriginNodePublicMethod(
            "static Number *newObj(double n) {\n"
            "        return new Number(n);\n"
            "    }\n"
    ));
    addMethod(new OriginNodePublicMethod(
            "static Number *newObj(int n) {\n"
            "        return new Number(n);\n"
            "    }\n"
    ));
    // 加法
    addMethod(new OriginNodePublicMethod(
            "Object *plus(Object *obj) override {\n"
            "        auto num = dynamic_cast<Number *>(obj);\n"
            "        if (num == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        if (num->_isInt() && _isInt()) {\n"
            "            return Number::newObj(_integer + num->_integer);\n"
            "        } else if (num->_isInt()) {\n"
            "            return Number::newObj(_number + num->_integer);\n"
            "        } else if (_isInt()) {\n"
            "            return Number::newObj(_integer + num->_number);\n"
            "        } else {\n"
            "            return Number::newObj(_number + num->_number);\n"
            "        }\n"
            "    }\n"
    ));
    // 减法
    addMethod(new OriginNodePublicMethod(
            "Object *minus(Object *obj) override {\n"
            "        auto num = dynamic_cast<Number *>(obj);\n"
            "        if (num == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        if (num->_isInt() && _isInt()) {\n"
            "            return Number::newObj(_integer - num->_integer);\n"
            "        } else if (num->_isInt()) {\n"
            "            return Number::newObj(_number - num->_integer);\n"
            "        } else if (_isInt()) {\n"
            "            return Number::newObj(_integer - num->_number);\n"
            "        } else {\n"
            "            return Number::newObj(_number - num->_number);\n"
            "        }\n"
            "    }\n"
    ));
    // 乘法
    addMethod(new OriginNodePublicMethod(
            "Object *times(Object *obj) override {\n"
            "        auto num = dynamic_cast<Number *>(obj);\n"
            "        if (num == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        if (num->_isInt() && _isInt()) {\n"
            "            return Number::newObj(_integer * num->_integer);\n"
            "        } else if (num->_isInt()) {\n"
            "            return Number::newObj(_number * num->_integer);\n"
            "        } else if (_isInt()) {\n"
            "            return Number::newObj(_integer * num->_number);\n"
            "        } else {\n"
            "            return Number::newObj(_number * num->_number);\n"
            "        }\n"
            "    }\n"
    ));
    // 除法
    addMethod(new OriginNodePublicMethod(
            "Object *divide(Object *obj) override {\n"
            "        auto num = dynamic_cast<Number *>(obj);\n"
            "        if (num == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        if (num->_isInt() && _isInt()) {\n"
            "            if (_integer % num->_integer == 0) {\n"
            "                return Number::newObj(_integer / num->_integer);\n"
            "            } else {\n"
            "                return Number::newObj((double) _integer / num->_integer);\n"
            "            }\n"
            "        } else if (num->_isInt()) {\n"
            "            return Number::newObj(_number / num->_integer);\n"
            "        } else if (_isInt()) {\n"
            "            return Number::newObj(_integer / num->_number);\n"
            "        } else {\n"
            "            return Number::newObj(_number / num->_number);\n"
            "        }\n"
            "    }\n"
    ));
    // 求余数
    addMethod(new OriginNodePublicMethod(
            "Object *mod(Object *obj) override {\n"
            "        auto num = dynamic_cast<Number *>(obj);\n"
            "        if (num == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        return Number::newObj(_integer % num->_integer);\n"
            "    }\n"
    ));
    // <
    addMethod(new OriginNodePublicMethod(
            "auto num = dynamic_cast<Number *>(obj);\n"
            "        if (num == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        if (num->_isInt() && _isInt()) {\n"
            "            return _integer < num->_integer ? True::newObj() : nullptr;\n"
            "        } else if (num->_isInt()) {\n"
            "            return _number < num->_integer ? True::newObj() : nullptr;\n"
            "        } else if (_isInt()) {\n"
            "            return _integer < num->_number ? True::newObj() : nullptr;\n"
            "        } else {\n"
            "            return _number < num->_number ? True::newObj() : nullptr;\n"
            "        }\n"
    ));
    // <=
    addMethod(new OriginNodePublicMethod(
            "auto num = dynamic_cast<Number *>(obj);\n"
            "        if (num == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        if (num->_isInt() && _isInt()) {\n"
            "            return _integer <= num->_integer ? True::newObj() : nullptr;\n"
            "        } else if (num->_isInt()) {\n"
            "            return _number <= num->_integer ? True::newObj() : nullptr;\n"
            "        } else if (_isInt()) {\n"
            "            return _integer <= num->_number ? True::newObj() : nullptr;\n"
            "        } else {\n"
            "            return _number <= num->_number ? True::newObj() : nullptr;\n"
            "        }\n"
    ));
    // >
    addMethod(new OriginNodePublicMethod(
            "auto num = dynamic_cast<Number *>(obj);\n"
            "        if (num == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        if (num->_isInt() && _isInt()) {\n"
            "            return _integer > num->_integer ? True::newObj() : nullptr;\n"
            "        } else if (num->_isInt()) {\n"
            "            return _number > num->_integer ? True::newObj() : nullptr;\n"
            "        } else if (_isInt()) {\n"
            "            return _integer > num->_number ? True::newObj() : nullptr;\n"
            "        } else {\n"
            "            return _number > num->_number ? True::newObj() : nullptr;\n"
            "        }\n"
    ));
    // >=
    addMethod(new OriginNodePublicMethod(
            "auto num = dynamic_cast<Number *>(obj);\n"
            "        if (num == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        if (num->_isInt() && _isInt()) {\n"
            "            return _integer >= num->_integer ? True::newObj() : nullptr;\n"
            "        } else if (num->_isInt()) {\n"
            "            return _number >= num->_integer ? True::newObj() : nullptr;\n"
            "        } else if (_isInt()) {\n"
            "            return _integer >= num->_number ? True::newObj() : nullptr;\n"
            "        } else {\n"
            "            return _number >= num->_number ? True::newObj() : nullptr;\n"
            "        }\n"
    ));
    // ==
    addMethod(new OriginNodePublicMethod(
            "auto num = dynamic_cast<Number *>(obj);\n"
            "        if (num == nullptr) {\n"
            "            return nullptr;\n"
            "        }\n"
            "        if (num->_isInt() && _isInt()) {\n"
            "            return _integer == num->_integer ? True::newObj() : nullptr;\n"
            "        } else if (num->_isInt()) {\n"
            "            return _number == num->_integer ? True::newObj() : nullptr;\n"
            "        } else if (_isInt()) {\n"
            "            return _integer == num->_number ? True::newObj() : nullptr;\n"
            "        } else {\n"
            "            return _number == num->_number ? True::newObj() : nullptr;\n"
            "        }\n"
    ));
    addMethod(new OriginNodePublicMethod(
            "Object * toString() override {\n"
            "        if (_isInt()) {\n"
            "            return String::newObj(std::to_string(_integer));\n"
            "        }\n"
            "        return String::newObj(std::to_string(_number));\n"
            "    }\n"
    ));
}


