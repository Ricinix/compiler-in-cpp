//
// Created by laugh on 2020/12/15.
//

#ifndef DESIGN_1_CONSTANT_H
#define DESIGN_1_CONSTANT_H

enum class TokenType {
    eof, // end of file
    eol, // end of line
    identifier,
    number,
    string,
    op,
    none, // 默认赋值，代表没有类型
    reserve, // 保留字，给文法Rule用的
};

enum class OpType {
    none,
    plus, // +
    minus, // -
    times, // *
    divide, // /
    mod, // %
    equal, // ==
    less, // <
    more, // >
    lessEqual, // <=
    moreEqual, // >=
    logicalAnd, // &&
    logicalOr, // ||
    logicalNot, // !
    assign, // =
};

enum class VisibleType {
    privateType, // 可见性私有
    publicType, // 可见性公开
};

// 定义保留字

#define RW_WHILE "while"
#define RW_IF "if"
#define RW_ELSE "else"
#define RW_FUNC "function"
#define RW_RETURN "return"
#define RW_CLASS "class"
#define RW_EXTENDS "extends"
#define RW_STATIC "static"
#define RW_NEW "new"

// 定义非终结符

#define NS_PROGRAM "program"
#define NS_PROGRAM_BODY "programBody"
#define NS_STATEMENT_OR_NONE "statementOrNone"
#define NS_LINE_END "lineEnd"
#define NS_PROGRAM_STAR "programStar"
#define NS_STATEMENT "statement"
#define NS_EXPR "expr"
#define NS_EXPR_STAR "exprStar"
#define NS_BLOCK "block"
#define NS_BLOCK_STAR "blockStar"
#define NS_STATEMENT_STAR "statementStar"
#define NS_SIMPLE "simple"
#define NS_FACTOR "factor"
#define NS_PRIMARY "primary"
#define NS_PRIMARY_STAR "primaryStar"
#define NS_FUNC "func"
#define NS_POSTFIX "postfix"
#define NS_POSTFIX_OR_NONE "postfixOrNone"
#define NS_PARAM "param"
#define NS_PARAMS "params"
#define NS_PARAMS_STAR "params_star"
#define NS_PARAM_LIST "param_list"
#define NS_PARAM_LIST_OR_NONE "paramListOrNone"
#define NS_ARGS "args"
#define NS_ARGS_STAR "args_star"
#define NS_DECIMALS "decimals"
#define NS_RETURN "return"
#define NS_CLASS "class"
#define NS_EXTENDS "extends"
#define NS_CLASS_BODY "classBody"
#define NS_CLASS_BODY_STAR "classBodyStar"
#define NS_MEMBER_OR_NONE "memberOrNone"
#define NS_MEMBER "member"
#define NS_MEMBER_STAR "memberStar"
#define NS_STATIC_OR_NONE "staticOrNone"
#define NS_ELEMENTS "elements"
#define NS_ELEMENTS_OR_NONE "elementsOrNone"
#define NS_ELEMENTS_STAR "elementsStar"
#define NS_NEW "new"


#endif //DESIGN_1_CONSTANT_H
