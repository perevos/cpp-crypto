#pragma once

#include <string>
#include <map>

#include "OrderBookEntry.h"

class Wallet
{
public:
    Wallet();
    /** insert currency to the wallet */
    void insertCurrency(std::string type, double amount);
    /** remove currency from the wallet */
    bool removeCurrency(std::string type, double amount);
    /** check if the wallet contains this much currency or more */
    bool containsCurrency(std::string type, double amount) const;
    /** check if the wallet can cope with this ask or bid */
    bool canFulfillOrder(const OrderBookEntry& order) const;
    /** generate a string representation of the wallet */
    std::string toString() const;

private:
    bool canFulfillBidOrder(const OrderBookEntry& order) const;
    bool canFulfillAskOrder(const OrderBookEntry& order) const;
    std::map<std::string, double> currencies;
};
