#pragma once

#include <string>
#include "OrderBookType.h"

class OrderBookEntry
{
public:
    OrderBookEntry(double price, double amount, std::string timestamp, std::string product, OrderBookType orderType, std::string username = "dataset");
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
    std::string username;

    static bool compareByTimestamp(OrderBookEntry &e1, OrderBookEntry &e2);
    static bool compareByPriceAsc(OrderBookEntry &e1, OrderBookEntry &e2);
    static bool compareByPriceDesc(OrderBookEntry &e1, OrderBookEntry &e2);
};
