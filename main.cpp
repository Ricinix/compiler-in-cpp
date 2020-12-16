#include "lexer/Lexer.h"
#include "domain/OrderParser.h"

int main(int argc, char *argv[]) {
    Order order = OrderParser::parse(argc, argv);
    if (order.getOrderType() != OrderType::COMPILE) {
        IoUtil ioUtil(order.getSrcPath());
        Lexer lexer(ioUtil);
        Token* t_ptr = lexer.read();
        while(t_ptr != nullptr && t_ptr->getTokenType()!= TokenType::eof) {
            Log::info(*t_ptr);
            t_ptr = lexer.read();
        }
    }
    return 0;
}
