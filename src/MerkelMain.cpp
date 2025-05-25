#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include <iostream>
#include <vector>

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyze the market and make bids and offers." << std::endl;
}

void MerkelMain::printMarketStats()
{
    std::cout << "Order book contains (" << orders.size() << ") entries." << std::endl;
}

void MerkelMain::enterOffer()
{
    std::cout << "Mark and offer - enter the amount" << std::endl;
}

void MerkelMain::enterBid()
{
    std::cout << "Make a bid - enter the amount" << std::endl;
}

void MerkelMain::printWallet()
{
    std::cout << "Your wallet is empty." << std::endl;
}

void MerkelMain::gotoNextTimeFrame()
{
    std::cout << "Going to next time frame." << std::endl;
}

void handleInvalidOption()
{
    std::cout << "Invalid choice. Choose 1-6" << std::endl;
}

MerkelMain::MerkelMain() {

}

void MerkelMain::init() {

    loadOrderBook();
    for (OrderBookEntry& order : orders) {
        std::cout << "The price is " << order.price << std::endl;
    }
    int input;
    while (true) {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::loadOrderBook() {
    orders.push_back(OrderBookEntry{1000, 0.02, "2020/03/17 17:01:24.884492", "BTC/USDT", OrderBookType::bid});
    orders.push_back(OrderBookEntry{10000, 0.01, "2020/03/18 17:01:24.884492", "BTC/USDT", OrderBookType::ask});
}

void MerkelMain::printMenu() {
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Make an offer" << std::endl;
    std::cout << "4: Make a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
}

int MerkelMain::getUserOption() {
    std::cout << "================" << std::endl;
    std::cout << "Type in 1-6" << std::endl;

    int userOption;

    std::cin >> userOption;
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
    switch (userOption)
    {
    case 1:
        printHelp();
        break;
    case 2:
        printMarketStats();
        break;
    case 3:
        enterOffer();
        break;
    case 4:
        enterBid();
        break;
    case 5:
        printWallet();
        break;
    case 6:
        gotoNextTimeFrame();
        break;
    default:
        handleInvalidOption();
        break;
    }
    std::cout << std::endl;
}