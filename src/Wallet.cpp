#include <iostream>

#include "Wallet.h"
#include "CSVReader.h"

Wallet::Wallet()
{
}

void Wallet::insertCurrency(std::string type, double amount)
{
    if (amount < 0)
    {
        throw std::exception{};
    }

    double balance;
    if (currencies.count(type) == 0)
    {
        balance = 0;
    }
    else
    {
        balance = currencies[type];
    }
    balance += amount;
    currencies[type] = balance;
}

bool Wallet::containsCurrency(std::string type, double amount) const
{
    return currencies.count(type) != 0 && currencies.at(type) >= amount;
}

std::string Wallet::toString() const
{
    if (currencies.empty())
    {
        return "<empty wallet>";
    }

    std::string s;
    for (const std::pair<std::string, double> pair : currencies)
    {
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
    }
    return s;
}

bool Wallet::removeCurrency(std::string type, double amount)
{
    if (amount < 0)
    {
        throw std::exception{};
    }
    if (currencies.count(type) == 0)
    {
        return false;
    }
    else if (containsCurrency(type, amount))
    {
        currencies[type] -= amount;
        return true;
    }
    return false;
}

bool Wallet::canFulfillOrder(const OrderBookEntry& order) const
{
    switch (order.orderType)
    {
        case OrderBookType::ask:
            return canFulfillAskOrder(order);
        case OrderBookType::bid:
            return canFulfillBidOrder(order);
        default:
            return false;
    }
}

bool Wallet::canFulfillAskOrder(const OrderBookEntry& order) const
{
    std::vector<std::string> tokens = CSVReader::tokenise(order.product, '/');
    return containsCurrency(tokens[0], order.amount);
}

bool Wallet::canFulfillBidOrder(const OrderBookEntry& order) const
{
    std::vector<std::string> tokens = CSVReader::tokenise(order.product, '/');
    return containsCurrency(tokens[1], order.price * order.amount);
}

std::ostream& operator<<(std::ostream &os, Wallet& wallet)
{
    os << wallet.toString();
    return os;
}