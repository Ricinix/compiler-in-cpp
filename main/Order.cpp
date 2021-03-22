//
// Created by laugh on 2020/12/17.
//

#include "Order.h"
#include "../rule/SymbolTable.h"

RuleSet *CompileOrder::ruleSet = nullptr;
StateTransitionTable *CompileOrder::stateTransitionTable = nullptr;

Order::Order(const std::string &src, const std::string &target, OrderType type) {
    srcPath = src;
    targetPath = target;
    orderType = type;
}

const std::string &Order::getSrcPath() {
    return srcPath;
}

const std::string &Order::getTargetPath() {
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

CompileOrder::CompileOrder(const std::string &src, const std::string &target, OrderType type) : Order(src, target,
                                                                                                      type) {

}

void CompileOrder::exec() {
    Log::info("compiling" + getSrcPath());
    if (getRuleSet()->isLLOne()) {
        Log::info("check grammar is LL(1)");
    } else {
        Log::info("check grammar is not LL(1)");
    }
    IoUtil ioUtil(getSrcPath(), getTargetPath());
    SymbolTable::addModule(getSrcPath());
    auto *ast = getAst(ioUtil);
    // 打印cpp代码
    Log::info("final tree: ");
    Log::info(*ast);
    ast->generateCppCode(ioUtil);
    ioUtil.finish();
    // 通过g++生成exe
    generateExe(ioUtil);
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

AbstractSyntaxTree *CompileOrder::getAst(IoUtil &ioUtil) {
    // 词法分析
    Lexer lexer(ioUtil);
    // 语法分析
    Parser parser(getRuleSet(), &lexer, getStateTable());
    parser.parse();
    auto *parseTree = parser.getParseTree();
    Log::info(*parseTree);
    // 语法分析树转抽象语法树
    auto *ast = parseTree->toAST();
    Log::info(*ast);
    // 转cpp的抽象语法树
    AbstractSyntaxTree::ASTHelper helper(ioUtil.getInPath(), CompileOrder::getAstByInPath);
    ast->translateToCppTree(&helper);
    delete parseTree;
    return ast;
}

AbstractSyntaxTree *CompileOrder::getAstByInPath(const std::string &inPath) {
    Log::info("compiling" + inPath);
    IoUtil ioUtil(inPath);
    auto *ast = getAst(ioUtil);
    ioUtil.finish();
    return ast;
}

RuleSet *CompileOrder::getRuleSet() {
    if (ruleSet == nullptr) {
        ruleSet = RuleSet::generate();
    }
    return ruleSet;
}

StateTransitionTable *CompileOrder::getStateTable() {
    if (stateTransitionTable == nullptr) {
        stateTransitionTable = new StateTransitionTable(getRuleSet());
    }
    return stateTransitionTable;
}
