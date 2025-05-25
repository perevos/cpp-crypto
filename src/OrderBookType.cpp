#include "OrderBookType.h"

OrderBookType OrderBookTypeUtil::stringToOrderBookType(std::string typeString)
{
    if (typeString == "ask") {
        return OrderBookType::ask;
    }
    if (typeString == "bid") {
        return OrderBookType::bid;
    }
    return OrderBookType::unknown;
}
