#pragma once

#include <string>

enum class OrderBookType
{
    bid,
    ask,
    asksale,
    bidsale,
    unknown
};

class OrderBookTypeUtil
{
public:
    OrderBookTypeUtil() = default;
    static OrderBookType stringToOrderBookType(std::string typeString);
};
