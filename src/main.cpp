#include <iostream>
#include <vector>
#include <string>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "Tokenizer.h"
#include <fstream>

using namespace std;

int main()
{

    // MerkelMain app{};
    // app.init();

    std::ifstream csvFile{"../data/order-book.csv"};
    std::string line;
    std::vector<std::string> tokens;

    Tokenizer tokenizer{};

    if (csvFile.is_open())
    {
        std::cout << "File open " << std::endl;

        while (std::getline(csvFile, line))
        {
            tokens = tokenizer.tokenize(line, ',');
            if (tokens.size() != 5)
            {
                std::cout << "Bad line " << std::endl;
                continue;
            }

            try
            {
                double price = std::stod(tokens[3]);
                double amount = std::stod(tokens[4]);
                std::cout << price << ": " << amount << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
                break;
            }
        }

        csvFile.close();
    }
    else
    {
        std::cout << "Could not open file " << std::endl;
    }

    return 0;
}