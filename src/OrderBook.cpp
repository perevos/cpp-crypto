#include <map>
#include <algorithm>

#include "OrderBook.h"
#include "CSVReader.h"

OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;

    std::map<std::string, bool> prodMap;

    for (OrderBookEntry &e : orders)
    {
        prodMap[e.product] = true;
    }

    for (auto const &e : prodMap)
    {
        products.push_back(e.first);
    }

    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;

    for (OrderBookEntry &e : orders)
    {
        if (e.orderType == type && e.product == product && e.timestamp == timestamp)
        {
            orders_sub.push_back(e);
        }
    }

    return orders_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry> &orders)
{
    if (orders.empty())
    {
        throw std::exception{};
    }

    double max = orders[0].price;
    for (OrderBookEntry &e : orders)
    {
        if (e.price > max)
        {
            max = e.price;
        }
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry> &orders)
{
    if (orders.empty())
    {
        throw std::exception{};
    }

    double min = orders[0].price;
    for (OrderBookEntry &e : orders)
    {
        if (e.price < min)
        {
            min = e.price;
        }
    }
    return min;
}

std::string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
    std::string next_timestamp = "";
    for (OrderBookEntry &e : orders)
    {
        if (e.timestamp > timestamp)
        {
            next_timestamp = e.timestamp;
            break;
        }
    }
    if (next_timestamp == "")
    {
        next_timestamp = orders[0].timestamp;
    }
    return next_timestamp;
}

/**
 * Calculates the total volume of bids within a specified percentage deviation from the highest bid price.
 *
 * Args:
 *     - orders: a vector of OrderBookEntry objects representing the current bid orders.
 *     - maxDeviationPercentage: the maximum allowed percentage deviation from the best bid (e.g., 0.001 for 0.1%). Orders outside this range are excluded.
 *
 * Returns:
 *     the cumulative volume (sum of 'amount' for relevant bids) within the specified price range.
 */
double OrderBook::getBidVolumeByPriceDeviation(std::vector<OrderBookEntry> &orders, double maxDeviationPercentage)
{
    double bestBidPrice = getHighPrice(orders);
    double lowerBound = bestBidPrice * (1 - maxDeviationPercentage);
    double volume = 0;
    for (OrderBookEntry &e : orders)
    {
        if (e.price >= lowerBound)
        {
            volume += e.amount;
        }
    }
    return volume;
}

void OrderBook::insertOrder(OrderBookEntry &order)
{
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksAndBids(std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);

    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    std::vector<OrderBookEntry> sales;

    for (OrderBookEntry &ask : asks)
    {
        for (OrderBookEntry &bid : bids)
        {
            if (bid.price >= ask.price)
            {
                OrderBookEntry sale{ask.price, 0, timestamp, product, OrderBookType::asksale};
                if (bid.username == "simuser")
                {
                    sale.orderType = OrderBookType::bidsale;
                    sale.username = "simuser";
                }
                if (ask.username == "simuser")
                {
                    sale.orderType = OrderBookType::asksale;
                    sale.username = "simuser";
                }
                // TODO: this code does not handle the scenario when both ask and bid come from simuser.
                
                if (bid.amount == ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    ask.amount = 0;
                    bid.amount = 0;
                    break;
                }
                if (bid.amount > ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    ask.amount = 0;
                    bid.amount -= sale.amount;
                    break;
                }
                if (bid.amount < ask.amount)
                {
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount -= sale.amount;
                    bid.amount = 0;
                    continue;
                }
            }
        }
    }
    return sales;
}