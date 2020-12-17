#include "lexer/Lexer.h"
#include "domain/OrderParser.h"

int main(int argc, char *argv[]) {
    std::unique_ptr<Order> order_ptr = OrderParser::parse(argc, argv);
    if (order_ptr->getOrderType() != OrderType::COMPILE) {
        order_ptr->exec();
    }
    return 0;
}
