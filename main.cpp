#include "lexer/Lexer.h"
#include "main/OrderParser.h"

int main(int argc, char *argv[]) {
    std::unique_ptr<Order> order_ptr = OrderParser::parse(argc, argv);
    if (order_ptr != nullptr) {
        order_ptr->exec();
    } else {
        Log::error("null pointer of order");
    }
    return 0;
}
