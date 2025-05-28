#include <iostream>

#include "../Wallet.h"
#include "../OrderBookEntry.h"
#include "../OrderBookType.h"

int main()
{
    Wallet wallet;

    OrderBookEntry askOrder{0.01, 0.5, "2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::ask};

    assert(!wallet.canFulfillOrder(askOrder));

    wallet.insertCurrency("ETH", 0.4);
    assert(!wallet.canFulfillOrder(askOrder));

    wallet.insertCurrency("ETH", 0.1);
    assert(wallet.canFulfillOrder(askOrder));

    OrderBookEntry bidOrder{0.01, 0.5, "2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::bid};

    assert(!wallet.canFulfillOrder(bidOrder));

    wallet.insertCurrency("BTC", 0.0049);
    assert(!wallet.canFulfillOrder(bidOrder));

    wallet.insertCurrency("BTC", 0.0001);
    assert(wallet.canFulfillOrder(bidOrder));

    std::cout << "All tests have been successfully executed";
    return 0;
}