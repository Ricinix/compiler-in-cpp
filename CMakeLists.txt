cmake_minimum_required(VERSION 3.17)
project(design_1)

set(CMAKE_CXX_STANDARD 20)
# 设置exe输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
# 设置dll输出目录
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)

# main 目录下的文件
file(GLOB MAIN_CPP_PATH ./main/*.cpp)
file(GLOB MAIN_H_PATH ./main/*.h)
set(MAIN_PATH ${MAIN_CPP_PATH} ${MAIN_H_PATH})

# util 目录下的文件
file(GLOB UTIL_CPP_PATH ./util/*.cpp)
file(GLOB UTIL_H_PATH ./util/*.h)
set(UTIL_PATH ${UTIL_CPP_PATH} ${UTIL_H_PATH})

# domain 目录下的文件
file(GLOB DOMAIN_CPP_PATH ./domain/*.cpp)
file(GLOB DOMAIN_H_PATH ./domain/*.h)
set(DOMAIN_PATH ${DOMAIN_CPP_PATH} ${DOMAIN_H_PATH})

# lexer 目录下的文件
file(GLOB LEXER_CPP_PATH ./lexer/*.cpp)
file(GLOB LEXER_H_PATH ./lexer/*.h)
set(LEXER_PATH ${LEXER_CPP_PATH} ${LEXER_H_PATH})

# ast 目录下的文件
file(GLOB AST_CPP_PATH ./ast/*.cpp)
file(GLOB AST_H_PATH ./ast/*.h)
set(AST_PATH ${AST_CPP_PATH} ${AST_H_PATH})

# parser 目录下的文件
file(GLOB PARSER_CPP_PATH ./parser/*.cpp)
file(GLOB PARSER_H_PATH ./parser/*.h)
set(PARSER_PATH ${PARSER_CPP_PATH} ${PARSER_H_PATH})

# rule 目录下的文件
file(GLOB RULE_CPP_PATH ./rule/*.cpp)
file(GLOB RULE_H_PATH ./rule/*.h)
set(RULE_PATH ${RULE_CPP_PATH} ${RULE_H_PATH})

# generator 目录下的文件
file(GLOB GENERATOR_CPP_PATH ./generator/*.cpp)
file(GLOB GENERATOR_H_PATH ./generator/*.h)
set(GENERATOR_PATH ${GENERATOR_CPP_PATH} ${GENERATOR_H_PATH})

# 设置编译时搜索库的路径
link_directories(${LIBRARY_OUTPUT_PATH})

# 生成动态库
add_library(
        lexer
        SHARED
        ${UTIL_PATH}
        ${DOMAIN_PATH}
        ${LEXER_PATH}
        ${AST_PATH}
        ${PARSER_PATH}
        ${RULE_PATH}
        ${GENERATOR_PATH}
)

# 生成可执行文件
add_executable(
        design_1
        main.cpp
        ${MAIN_PATH}
)

# 连接动态库
target_link_libraries(
        design_1
        liblexer.dll
)