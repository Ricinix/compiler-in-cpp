//
// Created by laugh on 2021/3/14.
//

#ifndef DESIGN_1_OPNODEFETCHDOMAIN_H
#define DESIGN_1_OPNODEFETCHDOMAIN_H

#include "ASTNode.h"

class OpNodeFetchDomain : public ASTList {
private:
    ASTNode *prefixNode;
    ASTNode *domainNode;

    OpNodeFetchDomain(ASTNode *prefix, ASTNode *domain);

public:
    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;

    class Builder {
    private:
        ASTNode *prefixNode;
        ASTNode *domainNode;
    public:
        void setPrefixNode(ASTNode *prefix);

        void setDomainNode(ASTNode *domain);

        OpNodeFetchDomain *build();
    };

};


#endif //DESIGN_1_OPNODEFETCHDOMAIN_H
