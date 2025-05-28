#include <iostream>

#include "../Wallet.h"
#include "../OrderBookEntry.h"
#include "../OrderBookType.h"

void testInsertCurrency()
{
    Wallet wallet;

    std::cout << "Initial wallet state: " << wallet << std::endl << std::endl;

    wallet.insertCurrency("BTC", 1.0);
    std::cout << "Wallet after inserting 1 BTC:" << std::endl;
    std::cout << wallet << std::endl;

    wallet.insertCurrency("BTC", 0.5);
    std::cout << "Wallet after inserting another 0.5 BTC:" << std::endl;
    std::cout << wallet << std::endl;

    std::cout << "Trying to insert negative amount of BTC:" << std::endl;
    try
    {
        wallet.insertCurrency("BTC", -0.1);
    }
    catch (const std::exception &e)
    {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    std::cout << "Wallet after attempting to insert negative BTC:" << std::endl;
    std::cout << wallet << std::endl;
}

void testRemoveCurrency()
{
    Wallet wallet;
    wallet.insertCurrency("BTC", 1.0);
    std::cout << "Initial wallet state with 1 BTC:" << std::endl;
    std::cout << wallet << std::endl;

    std::cout << "Removing 0.5 BTC:" << std::endl;
    assert(wallet.removeCurrency("BTC", 0.5));
    std::cout << wallet << std::endl;

    std::cout << "Trying to remove 0.6 BTC (should fail):" << std::endl;
    assert(!wallet.removeCurrency("BTC", 0.6));
    std::cout << wallet << std::endl;

    std::cout << "Trying to remove non-existent currency (ETH):" << std::endl;
    assert(!wallet.removeCurrency("ETH", 0.1));
    std::cout << wallet << std::endl;

    std::cout << "Trying to remove negative amount of BTC:" << std::endl;
    try
    {
        wallet.removeCurrency("BTC", -0.1);
    }
    catch (const std::exception &e)
    {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    std::cout << "Wallet after attempting to remove negative BTC:" << std::endl;
    std::cout << wallet << std::endl;
}

void testContainsCurrency()
{
    Wallet wallet;
    wallet.insertCurrency("BTC", 1.0);
    std::cout << "Initial wallet state with 1 BTC:" << std::endl;
    std::cout << wallet << std::endl;

    assert(wallet.containsCurrency("BTC", 1.0));
    std::cout << "Wallet contains 1 BTC" << std::endl;

    assert(wallet.containsCurrency("BTC", 0.5));
    std::cout << "Wallet contains 0.5 BTC" << std::endl;

    assert(!wallet.containsCurrency("BTC", 1.5));
    std::cout << "Wallet does not contain 1.5 BTC" << std::endl;
}

void testCanFulfillAskOrder()
{
    Wallet wallet;

    OrderBookEntry askOrder{0.01, 0.5, "2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::ask};

    std::cout << "Checking if wallet can fulfill ask order:" << std::endl;
    assert(!wallet.canFulfillOrder(askOrder));

    wallet.insertCurrency("ETH", 0.4);
    assert(!wallet.canFulfillOrder(askOrder));

    wallet.insertCurrency("ETH", 0.1);
    assert(wallet.canFulfillOrder(askOrder));

    std::cout << "All checks passed for ask order." << std::endl;
    std::cout << wallet << std::endl;
}

void testCanFulfillBidOrder()
{
    Wallet wallet;

    OrderBookEntry bidOrder{0.01, 0.5, "2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::bid};

    std::cout << "Checking if wallet can fulfill bid order:" << std::endl;
    assert(!wallet.canFulfillOrder(bidOrder));

    wallet.insertCurrency("BTC", 0.0049);
    assert(!wallet.canFulfillOrder(bidOrder));

    wallet.insertCurrency("BTC", 0.0001);
    assert(wallet.canFulfillOrder(bidOrder));

    std::cout << "All checks passed for bid order." << std::endl;
    std::cout << wallet << std::endl;
}

int main()
{
    testInsertCurrency();
    // testRemoveCurrency();
    // testContainsCurrency();
}