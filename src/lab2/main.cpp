#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>

enum class OrderBookType{bid, ask};

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

OrderBookEntry::OrderBookEntry(double price, double amount, std::string timestamp, std::string product, OrderBookType orderType):
    price{price}, amount(amount), timestamp(timestamp), product(product), orderType(orderType)
{
}

double computeAveragePrice(std::vector<OrderBookEntry>& entries) {
    if (entries.size() == 0) {
        // Here, for simplicity, we use the convention 0/0 = 0.
        return 0;
    }
    double sum = 0;
    for (OrderBookEntry& entry : entries) {
        sum += entry.price;
    }
    return sum / entries.size();
}

double computeLowPrice(std::vector<OrderBookEntry>& entries) {
    // If there are no entries, we return the maximal element of double
    double lowPrice = std::numeric_limits<double>::max();
    for (OrderBookEntry& entry : entries) {
        if (entry.price < lowPrice) {
            lowPrice = entry.price;
        }
    }
    return lowPrice;
}

double computeHighPrice(std::vector<OrderBookEntry>& entries) {
    // If there are no entries, we return the minimal element of double
    double highPrice = std::numeric_limits<double>::min();
    for (OrderBookEntry& entry : entries) {
        if (entry.price > highPrice) {
            highPrice = entry.price;
        }
    }
    return highPrice;
}

double computePriceSpread(std::vector<OrderBookEntry>& entries) {
    if (entries.size() == 0) {
        // We assume that the price spread of an empty list equals zero.
        return 0;
    }
    return computeHighPrice(entries) - computeLowPrice(entries);
}

int main() {
    OrderBookEntry obe1{0.02187308, 7.44564869, "2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::bid};
    OrderBookEntry obe2{0.00000047, 10796386.702639, "2020/03/17 17:01:24.884492", "DOGE/BTC", OrderBookType::ask};
    
    std::vector<OrderBookEntry> entries;
    entries.push_back(obe1);
    entries.push_back(obe2);

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Average price is: " << computeAveragePrice(entries) << std::endl;
    std::cout << "Low price is: " << computeLowPrice(entries) << std::endl;
    std::cout << "High price is: " << computeHighPrice(entries) << std::endl;
    std::cout << "Price spread is: " << computePriceSpread(entries) << std::endl;

    return 0;
}