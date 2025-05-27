#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(double price, double amount, std::string timestamp, std::string product, OrderBookType orderType) : price{price}, amount(amount), timestamp(timestamp), product(product), orderType(orderType)
{
}

bool OrderBookEntry::compareByTimestamp(OrderBookEntry &e1, OrderBookEntry &e2) {
    return e1.timestamp < e2.timestamp;
}
