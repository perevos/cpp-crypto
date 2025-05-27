#pragma once

#include <string>
#include <vector>

#include "OrderBookEntry.h"
#include "CSVReader.h"

class OrderBook
{
public:
    /** construct, reading a CSV data file */
    OrderBook(std::string filename);
    /** return vector of all known products in the dataset */
    std::vector<std::string> getKnownProducts();
    /** return vector of Orders according to the sent filters */
    std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);
    /** return the earliest time in the orderbook */
    std::string getEarliestTime();
    /** return the next time after the sent time in the orderbook;
     *  if there is not next timestamp, wrap around to the start;
     */
    std::string getNextTime(std::string timestamp);

    void insertOrder(OrderBookEntry& order);

    /** return the price of the highest bid in the sent set */
    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    /** return the price of the lowest bid in the sent set */
    static double getLowPrice(std::vector<OrderBookEntry>& orders);
    /** return the total volume of bids within a specified percentage deviation from the highest bid price */
    static double getBidVolumeByPriceDeviation(std::vector<OrderBookEntry>& orders, double maxDeviationPercentage);

private:
    std::vector<OrderBookEntry> orders;
};
