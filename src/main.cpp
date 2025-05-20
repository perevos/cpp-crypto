#include <iostream>

void printMenu()
{
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Make an offer" << std::endl;
    std::cout << "4: Make a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
}

int getUserOption()
{
    std::cout << "================" << std::endl;
    std::cout << "Type in 1-6" << std::endl;

    int userOption;

    std::cin >> userOption;
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void printHelp()
{
    std::cout << "Help - your aim is to make money. Analyze the market and make bids and offers." << std::endl;
}

void printExchangeStats()
{
    std::cout << "Market looks good" << std::endl;
}

void enterOffer()
{
    std::cout << "Mark and offer - enter the amount" << std::endl;
}

void enterBid()
{
    std::cout << "Make a bid - enter the amount" << std::endl;
}

void printWallet()
{
    std::cout << "Your wallet is empty." << std::endl;
}

void goToNextTimeFrame()
{
    std::cout << "Going to next time frame." << std::endl;
}

void handleInvalidOption()
{
    std::cout << "Invalid choice. Choose 1-6" << std::endl;
}

void processUserOption(int userOption)
{
    switch (userOption)
    {
    case 1:
        printHelp();
        break;
    case 2:
        printExchangeStats();
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
        goToNextTimeFrame();
        break;
    default:
        handleInvalidOption();
        break;
    }
    std::cout << std::endl;
}

int main()
{
    while (true)
    {
        printMenu();
        int userOption = getUserOption();
        processUserOption(userOption);
    }

    return 0;
}