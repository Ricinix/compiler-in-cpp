//
// Created by laugh on 2021/3/16.
//

#ifndef DESIGN_1_ORIGINBASEFUNCDEFINENODE_H
#define DESIGN_1_ORIGINBASEFUNCDEFINENODE_H

#include "DefineNodeFunction.h"

class OriginBaseFuncDefineNode : public DefineNodeFunction{
public:
    std::string toString() const override;
    void genCode(IoUtil &ioUtil) override;
    std::string getHashMsg() override;
};


#endif //DESIGN_1_ORIGINBASEFUNCDEFINENODE_H
