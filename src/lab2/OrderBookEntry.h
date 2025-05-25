#pragma once

#include <string>
#include "OrderBookType.h"

class OrderBookEntry
{
    public:
        OrderBookEntry(double price, double amount, std::string timestamp, std::string product, OrderBookType orderType);
        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;
};
