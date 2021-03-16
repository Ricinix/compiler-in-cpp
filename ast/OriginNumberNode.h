//
// Created by laugh on 2021/3/15.
//

#ifndef DESIGN_1_ORIGINNUMBERNODE_H
#define DESIGN_1_ORIGINNUMBERNODE_H

#include "OriginObjectNode.h"
#include "OriginStringNode.h"


class Number : public Object {
private:
    int _integer = 0;
    double _number = 0;
    bool _isInteger = true;
    bool _isInt() {
        return _isInteger;
    }
public:
    explicit Number(int n) {
        _integer = n;
    }

    explicit Number(double n) {
        _number = n;
        _isInteger = false;
    }

    static Number *newObj(double n) {
        return new Number(n);
    }

    static Number *newObj(int n) {
        return new Number(n);
    }

    Object *plus(Object *obj) override {
        auto num = dynamic_cast<Number *>(obj);
        if (num == nullptr) {
            return nullptr;
        }
        if (num->_isInt() && _isInt()) {
            return Number::newObj(_integer + num->_integer);
        } else if (num->_isInt()) {
            return Number::newObj(_number + num->_integer);
        } else if (_isInt()) {
            return Number::newObj(_integer + num->_number);
        } else {
            return Number::newObj(_number + num->_number);
        }
    }

    Object *minus(Object *obj) override {
        auto num = dynamic_cast<Number *>(obj);
        if (num == nullptr) {
            return nullptr;
        }
        if (num->_isInt() && _isInt()) {
            return Number::newObj(_integer - num->_integer);
        } else if (num->_isInt()) {
            return Number::newObj(_number - num->_integer);
        } else if (_isInt()) {
            return Number::newObj(_integer - num->_number);
        } else {
            return Number::newObj(_number - num->_number);
        }
    }

    Object *times(Object *obj) override {
        auto num = dynamic_cast<Number *>(obj);
        if (num == nullptr) {
            return nullptr;
        }
        if (num->_isInt() && _isInt()) {
            return Number::newObj(_integer * num->_integer);
        } else if (num->_isInt()) {
            return Number::newObj(_number * num->_integer);
        } else if (_isInt()) {
            return Number::newObj(_integer * num->_number);
        } else {
            return Number::newObj(_number * num->_number);
        }
    }

    Object *divide(Object *obj) override {
        auto num = dynamic_cast<Number *>(obj);
        if (num == nullptr) {
            return nullptr;
        }
        if (num->_isInt() && _isInt()) {
            if (_integer % num->_integer == 0) {
                return Number::newObj(_integer / num->_integer);
            } else {
                return Number::newObj((double) _integer / num->_integer);
            }
        } else if (num->_isInt()) {
            return Number::newObj(_number / num->_integer);
        } else if (_isInt()) {
            return Number::newObj(_integer / num->_number);
        } else {
            return Number::newObj(_number / num->_number);
        }
    }

    Object *mod(Object *obj) override {
        auto num = dynamic_cast<Number *>(obj);
        if (num == nullptr) {
            return nullptr;
        }
        return Number::newObj(_integer % num->_integer);
    }

    Object * lessThan(Object *obj) override {
        auto num = dynamic_cast<Number *>(obj);
        if (num == nullptr) {
            return nullptr;
        }
        if (num->_isInt() && _isInt()) {
            return _integer < num->_integer ? True::newObj() : nullptr;
        } else if (num->_isInt()) {
            return _number < num->_integer ? True::newObj() : nullptr;
        } else if (_isInt()) {
            return _integer < num->_number ? True::newObj() : nullptr;
        } else {
            return _number < num->_number ? True::newObj() : nullptr;
        }
    }

    Object * lessEqualThan(Object *obj) override {
        auto num = dynamic_cast<Number *>(obj);
        if (num == nullptr) {
            return nullptr;
        }
        if (num->_isInt() && _isInt()) {
            return _integer <= num->_integer ? True::newObj() : nullptr;
        } else if (num->_isInt()) {
            return _number <= num->_integer ? True::newObj() : nullptr;
        } else if (_isInt()) {
            return _integer <= num->_number ? True::newObj() : nullptr;
        } else {
            return _number <= num->_number ? True::newObj() : nullptr;
        }
    }

    Object * moreThan(Object *obj) override {
        auto num = dynamic_cast<Number *>(obj);
        if (num == nullptr) {
            return nullptr;
        }
        if (num->_isInt() && _isInt()) {
            return _integer > num->_integer ? True::newObj() : nullptr;
        } else if (num->_isInt()) {
            return _number > num->_integer ? True::newObj() : nullptr;
        } else if (_isInt()) {
            return _integer > num->_number ? True::newObj() : nullptr;
        } else {
            return _number > num->_number ? True::newObj() : nullptr;
        }
    }

    Object * moreEqualThan(Object *obj) override {
        auto num = dynamic_cast<Number *>(obj);
        if (num == nullptr) {
            return nullptr;
        }
        if (num->_isInt() && _isInt()) {
            return _integer >= num->_integer ? True::newObj() : nullptr;
        } else if (num->_isInt()) {
            return _number >= num->_integer ? True::newObj() : nullptr;
        } else if (_isInt()) {
            return _integer >= num->_number ? True::newObj() : nullptr;
        } else {
            return _number >= num->_number ? True::newObj() : nullptr;
        }
    }

    Object * equal(Object *obj) override {
        auto num = dynamic_cast<Number *>(obj);
        if (num == nullptr) {
            return nullptr;
        }
        if (num->_isInt() && _isInt()) {
            return _integer == num->_integer ? True::newObj() : nullptr;
        } else if (num->_isInt()) {
            return _number == num->_integer ? True::newObj() : nullptr;
        } else if (_isInt()) {
            return _integer == num->_number ? True::newObj() : nullptr;
        } else {
            return _number == num->_number ? True::newObj() : nullptr;
        }
    }

    Object * toString() override {
        if (_isInt()) {
            return String::newObj(std::to_string(_integer));
        }
        return String::newObj(std::to_string(_number));
    }
};

class OriginNumberNode : public OriginObjectNode {
public:
    void genCode(IoUtil &ioUtil) override;
    std::string toString() const override;
};



#endif //DESIGN_1_ORIGINNUMBERNODE_H
