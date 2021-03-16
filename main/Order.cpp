//
// Created by laugh on 2020/12/17.
//

#include "Order.h"
#include "../util/Log.h"
#include "../lexer/Lexer.h"

Order::Order(std::string &src, std::string &target, OrderType type) {
    srcPath = src;
    targetPath = target;
    orderType = type;
}

std::string Order::getSrcPath() {
    return srcPath;
}

std::string Order::getTargetPath() {
    return targetPath;
}

OrderType Order::getOrderType() {
    return orderType;
}

Order::Order() {
    orderType = OrderType::ERROR;
}

void Order::exec() {
    Log::warm("do nothing");
}

CompileOrder::CompileOrder(std::string &src, std::string &target, OrderType type) : Order(src, target, type) {

}

void CompileOrder::exec() {
    Log::info("compiling" + getSrcPath());
    IoUtil ioUtil(getSrcPath(), getTargetPath());
    auto *lexer_ptr = new Lexer(ioUtil);
    auto *ruleSet = RuleSet::generate();
    Parser parser(ruleSet, lexer_ptr);
    parser.parse();
    auto parseTree = parser.getParseTree();
    Log::info(*parseTree);
    auto *ast = parseTree->toAST();
    Log::info(*ast);

    auto *helper = new AbstractSyntaxTree::ASTHelper();
    helper->load = CompileOrder::getAst;

    ast->translateToCppTree(helper);
    ast->generateCppCode(ioUtil);
    generateExe(ioUtil);
}

AbstractSyntaxTree *CompileOrder::getAst(const std::string &inPath) {
    Log::info("compiling " + inPath);
    IoUtil ioUtil(inPath);
    auto *lexer_ptr = new Lexer(ioUtil);
    auto *ruleSet = RuleSet::generate();
    Parser parser(ruleSet, lexer_ptr);
    parser.parse();
    auto parseTree = parser.getParseTree();
    Log::info(*parseTree);
    auto *ast = parseTree->toAST();
    Log::info(*ast);
    return ast;
}

void CompileOrder::generateExe(IoUtil &ioUtil) {
    std::ostringstream fmt;
    std::string exePath = ioUtil.getOutPath();
    fmt << R"(mingw\mingw32\bin\g++ )";
    fmt << ioUtil.getOutPath();
    fmt << " -o ";
    int lastIndex = exePath.find_last_of('.');
    fmt << exePath.replace(lastIndex, exePath.size() - lastIndex, ".exe");
    Log::info(fmt.str());
    system(fmt.str().c_str());
}
