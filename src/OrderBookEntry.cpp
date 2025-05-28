#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(double price, double amount, std::string timestamp, std::string product, OrderBookType orderType, std::string username) : price{price}, amount(amount), timestamp(timestamp), product(product), orderType(orderType), username(username)
{
}

bool OrderBookEntry::compareByTimestamp(OrderBookEntry &e1, OrderBookEntry &e2) {
    return e1.timestamp < e2.timestamp;
}

bool OrderBookEntry::compareByPriceAsc(OrderBookEntry &e1, OrderBookEntry &e2)
{
    return e1.price < e2.price;
}

bool OrderBookEntry::compareByPriceDesc(OrderBookEntry &e1, OrderBookEntry &e2)
{
    return e1.price > e2.price;
}