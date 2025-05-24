#ifndef MERKELMAIN_H
#define MERKELMAIN_H

class MerkelMain
{
    public:
        MerkelMain();
        /** Call this to start the sim */
        void init();
        void printMenu();
        int getUserOption();
        void processUserOption(int userOption);
        void printHelp();
        void printMarketStats();
        void enterOffer();
        void enterBid();
        void printWallet();
        void gotoNextTimeFrame();
};

#endif