#include <iostream>

#include "MerkelMain.h"
#include "CSVReader.h"

MerkelMain::MerkelMain()
{
}

void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();
    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Make an ask" << std::endl;
    std::cout << "4: Make a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
    std::cout << "================" << std::endl;
    std::cout << "Current time is: " << currentTime << std::endl;
}

int MerkelMain::getUserOption()
{
    std::cout << "Type in 1-6" << std::endl;

    std::string line;
    std::getline(std::cin, line);
    try
    {
        int userOption = std::stod(line);
        std::cout << "You chose: " << userOption << std::endl;
        return userOption;
    }
    catch (const std::exception &e)
    {
        return 0;
    }
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
        enterAsk();
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
    std::cout << "Press any key to continue..." << std::endl;
    std::cin.get();
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyze the market and make bids and offers." << std::endl;
}

void MerkelMain::printMarketStats()
{
    for (std::string const p : orderBook.getKnownProducts())
    {
        std::cout << std::endl
                  << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> bidEntries = orderBook.getOrders(OrderBookType::bid, p, currentTime);
        std::cout << "Bids seen: " << bidEntries.size() << std::endl;
        std::cout << "Best bid: " << OrderBook::getHighPrice(bidEntries) << std::endl;
        // std::cout << "0.1% bid depth: " << OrderBook::getBidVolumeByPriceDeviation(bidEntries, 0.001) << std::endl;

        std::vector<OrderBookEntry> askEntries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::cout << "Asks seen: " << askEntries.size() << std::endl;
        std::cout << "Best ask: " << OrderBook::getLowPrice(askEntries) << std::endl;
    }
}

void MerkelMain::enterAsk()
{
    std::cout << "Make an ask - enter the amount: product, price, amount, e.g. ETH/BTC,200,0.5" << std::endl;
    std::string input;
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "Bad input! " << input << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask);
            orderBook.insertOrder(obe);
        }
        catch (const std::exception &e)
        {
            std::cout << "MerkelMain::enterAsk: Bad input! " << std::endl;
        }
    }

    std::cout << "You typed: " << input << std::endl;
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
    currentTime = orderBook.getNextTime(currentTime);
}

void MerkelMain::handleInvalidOption()
{
    std::cout << "Invalid choice. Choose 1-6" << std::endl;
}