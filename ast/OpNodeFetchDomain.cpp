//
// Created by laugh on 2021/3/14.
//

#include "OpNodeFetchDomain.h"
#include "OpNodeCallFunction.h"
#include "../rule/SymbolTable.h"

std::string OpNodeFetchDomain::toString() const {
    return ".";
}

OpNodeFetchDomain::OpNodeFetchDomain(ASTNode *prefix, ASTNode *domain) {
    prefixNode = prefix;
    domainNode = domain;
    addChild(prefix);
    addChild(domain);
}

void OpNodeFetchDomain::genCode(IoUtil &ioUtil) {
    prefixNode->genCode(ioUtil);
    if (prefixNode->getType() == ASTNodeType::id && domainNode->getType() == ASTNodeType::funcCall) {
        auto *fc = dynamic_cast<OpNodeCallFunction *>(domainNode);
        if (fc != nullptr && SymbolTable::isStaticMethod(prefixNode->toString() + "::" + fc->getHashMsg())) {
            ioUtil.appendContent("::");
        } else {
            ioUtil.appendContent("->");
        }
    } else {
        ioUtil.appendContent("->");
    }
    domainNode->genCode(ioUtil);
}

ASTNodeType OpNodeFetchDomain::getType() {
    return ASTNodeType::opFetchDomain;
}

void OpNodeFetchDomain::Builder::setPrefixNode(ASTNode *prefix) {
    prefixNode = prefix;
}

void OpNodeFetchDomain::Builder::setDomainNode(ASTNode *domain) {
    domainNode = domain;
}

OpNodeFetchDomain *OpNodeFetchDomain::Builder::build() {
    return new OpNodeFetchDomain(prefixNode, domainNode);
}
