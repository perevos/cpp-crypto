#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"

int main()
{
    MerkelMain app = MerkelMain();

    while (true)
    {
        app.printMenu();
        int userOption = app.getUserOption();
        app.processUserOption(userOption);
    }

    return 0;
}