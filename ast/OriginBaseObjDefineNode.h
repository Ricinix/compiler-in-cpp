//
// Created by laugh on 2021/3/16.
//

#ifndef DESIGN_1_ORIGINBASEOBJDEFINENODE_H
#define DESIGN_1_ORIGINBASEOBJDEFINENODE_H

#include "DefineNodeObject.h"

class OriginBaseObjDefineNode : public DefineNodeObject{
public:
    std::string toString() const override;
    void genCode(IoUtil &ioUtil) override;
};


#endif //DESIGN_1_ORIGINBASEOBJDEFINENODE_H
