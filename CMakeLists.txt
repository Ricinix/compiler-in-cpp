cmake_minimum_required(VERSION 3.17)
project(design_1)

set(CMAKE_CXX_STANDARD 20)

# util 目录下的文件
file(GLOB UTIL_CPP_PATH ./util/*.cpp)
file(GLOB UTIL_H_PATH ./util/*.h)
set(UTIL_PATH ${UTIL_CPP_PATH} ${UTIL_H_PATH})

# domain 目录下的文件
file(GLOB DOMAIN_CPP_PATH ./domain/*.cpp)
file(GLOB DOMAIN_H_PATH ./domain/*.h)
set(DOMAIN_PATH ${DOMAIN_CPP_PATH} ${DOMAIN_H_PATH})

# lexer目录下的文件
file(GLOB LEXER_CPP_PATH ./lexer/*.cpp)
file(GLOB LEXER_H_PATH ./lexer/*.h)
set(LEXER_PATH ${LEXER_CPP_PATH} ${LEXER_H_PATH})

# 生成动态库
add_library(
        lexer
        SHARED
        ${UTIL_PATH}
        ${DOMAIN_PATH}
        ${LEXER_PATH}
)

# 生成可执行文件
add_executable(
        design_1
        main.cpp
)

# 连接动态库
target_link_libraries(
        design_1
        ${CMAKE_CURRENT_BINARY_DIR}/liblexer.dll
)