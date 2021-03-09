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

// 定义保留字

#define RW_WHILE "while"
#define RW_IF "if"
#define RW_ELSE "else"

// 定义非终结符

#define NS_PROGRAM "program"
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


#endif //DESIGN_1_CONSTANT_H
