#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

class MerkelMain
{
    public:
        MerkelMain();
        /** Call this to start the sim */
        void init();
    private:
        void loadOrderBook();
        void printMenu();
        int getUserOption();
        void processUserOption(int userOption);
        void printHelp();
        void printMarketStats();
        void enterOffer();
        void enterBid();
        void printWallet();
        void gotoNextTimeFrame();

        OrderBook orderBook{"../data/order-book.csv"};
};
