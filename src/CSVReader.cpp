#include <iostream>
#include <fstream>

#include "CSVReader.h"
#include "OrderBookType.h"

CSVReader::CSVReader()
{
}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename)
{
    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{csvFilename};
    std::string line;

    if (!csvFile.is_open())
    {
        std::cerr << "Could not open file " << std::endl;
        throw;
    }

    while (std::getline(csvFile, line))
    {
        try
        {
            OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
            entries.push_back(obe);
        }
        catch(const std::exception& e) {
            std::cerr << "CSVReader::readCSV corrupted csv line: " << line << std::endl;
        }
    }

    std::cout << "CSVReader::readCSV read " << entries.size() << " entries" << std::endl;

    csvFile.close();
    return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
    std::vector<std::string> tokens{};

    if (!csvLine.length())
    {
        return tokens;
    }

    signed int start = 0;
    signed int end = start;

    do
    {
        end = csvLine.find_first_of(separator, start);
        if (end >= 0)
        {
            tokens.push_back(csvLine.substr(start, end - start));
        }
        else
        {
            tokens.push_back(csvLine.substr(start, csvLine.length() - start));
        }
        start = end + 1;
    } while (end >= 0);

    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    if (tokens.size() != 5)
    {
        std::cerr << "Bad line " << std::endl;
        throw std::exception{};
    }

    double price;
    try
    {
        price = std::stod(tokens[3]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Malformed price! " << tokens[3] << std::endl;
        throw e;
    }

    double amount;
    try
    {
        price = std::stod(tokens[4]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Malformed amount! " << tokens[3] << std::endl;
        throw e;
    }

    OrderBookEntry obe{price, amount, tokens[0], tokens[1], OrderBookTypeUtil::stringToOrderBookType(tokens[2])};
    return obe;
}
