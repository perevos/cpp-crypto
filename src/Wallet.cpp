#include "Wallet.h"

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

bool Wallet::containsCurrency(std::string type, double amount)
{
    return currencies.count(type) != 0 && currencies[type] >= amount;
}

std::string Wallet::toString()
{
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