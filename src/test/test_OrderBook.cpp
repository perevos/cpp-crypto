#include <iostream>
#include "../OrderBook.h"
#include "../OrderBookType.h"

int main() {
    OrderBook orderBook{"test-order-book.csv"};
    std::vector<OrderBookEntry> orders = orderBook.getOrders(OrderBookType::bid, "ETH/BTC", "2020/03/17 17:01:24.884492");
    double bidDepth = orderBook.getBidVolumeByPriceDeviation(orders, 0.001);
    std::cout << "0.1% bid depth: " << bidDepth << std::endl;
    return 0;
}