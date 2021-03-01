//
// Created by laugh on 2020/12/15.
//

#ifndef DESIGN_1_CONSTANT_H
#define DESIGN_1_CONSTANT_H

enum class TokenType{
    eof, // end of file
    eol, // end of line
    identifier,
    number,
    string,
    op,
    none, // 默认赋值，代表没有类型
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

#endif //DESIGN_1_CONSTANT_H
