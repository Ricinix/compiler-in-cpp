//
// Created by laugh on 2021/3/15.
//

#ifndef DESIGN_1_ORIGINOBJECTNODE_H
#define DESIGN_1_ORIGINOBJECTNODE_H

#include "DefineNodeObject.h"

class OriginObjectNode : public DefineNodeObject {
protected:
    std::vector<DefineNodeDomain *> domainSet;

    std::vector<DecorateNodeMethod *> methodSet;

public:
    OriginObjectNode();

    std::string toString() const override;

    void genCode(IoUtil &ioUtil) override;

    void addDomain(DefineNodeDomain *domain) override;

    void addMethod(DecorateNodeMethod *method) override;
};

class Object {
public:
    static Object *newObj() {
        return new Object;
    }
    virtual Object *plus(Object *obj) { return nullptr; }

    virtual Object *minus(Object *obj) { return nullptr; }

    virtual Object *divide(Object *obj) { return nullptr; }

    virtual Object *times(Object *obj) { return nullptr; }

    virtual Object *mod(Object *obj) { return nullptr; }

    virtual Object *lessThan(Object *obj) { return nullptr; }

    virtual Object *lessEqualThan(Object *obj) { return nullptr; }

    virtual Object *moreThan(Object *obj) { return nullptr; }

    virtual Object *moreEqualThan(Object *obj) { return nullptr; }

    virtual Object *equal(Object *obj) { return nullptr; }

    virtual Object *toString() { return nullptr; }

    virtual Object *hashCode() { return nullptr; }
};

class OriginTrueNode : public OriginObjectNode {
private:
    bool isInit = false;
    void init();
public:
    void genCode(IoUtil &ioUtil) override;
};

class True : public Object {
public:
    static True *newObj() {
        return new True;
    }
};

#endif //DESIGN_1_ORIGINOBJECTNODE_H
