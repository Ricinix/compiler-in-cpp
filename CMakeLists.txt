cmake_minimum_required(VERSION 3.17)
project(design_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(design_1 main.cpp util/IoUtil.cpp util/IoUtil.h util/Log.h lexer/Token.cpp lexer/Token.h domain/constant.h domain/exception.h lexer/Lexer.cpp lexer/Lexer.h lexer/RegexPat.cpp lexer/RegexPat.h domain/exception.cpp domain/OrderParser.cpp domain/OrderParser.h domain/Order.cpp domain/Order.h)