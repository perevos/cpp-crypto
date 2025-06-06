#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

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
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeFrame();
        void handleInvalidOption();

        std::string currentTime;

        OrderBook orderBook{"../data/order-book.csv"};
        Wallet wallet;
};
