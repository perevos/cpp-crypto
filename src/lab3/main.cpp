#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

class StockPriceHistoryEntry
{
public:
    StockPriceHistoryEntry(std::string timestamp, double openPrice, double highPrice, double lowPrice, double closePrice, double volume, double dividends, double stockSplits);
    std::string timestamp;
    double openPrice;
    double highPrice;
    double lowPrice;
    double closePrice;
    double volume;
    double dividends;
    double stockSplits;
};

StockPriceHistoryEntry::StockPriceHistoryEntry(std::string timestamp, double openPrice, double highPrice, double lowPrice, double closePrice, double volume, double dividends, double stockSplits) : timestamp(timestamp), openPrice(openPrice), highPrice(highPrice), lowPrice(lowPrice), closePrice(closePrice), volume(volume), dividends(dividends), stockSplits(stockSplits)
{
}

std::vector<std::string> tokenize(std::string csv, char separator)
{
    std::vector<std::string> tokens{};

    if (!csv.length())
    {
        return tokens;
    }

    signed int start = 0;
    signed int end = start;

    do
    {
        end = csv.find_first_of(separator, start);
        if (end >= 0)
        {
            tokens.push_back(csv.substr(start, end - start));
        }
        else
        {
            tokens.push_back(csv.substr(start, csv.length() - start));
        }
        start = end + 1;
    } while (end != std::string::npos);

    return tokens;
}

double calculateSimpleAverageStockPrice(std::vector<StockPriceHistoryEntry> &stockPriceHistory)
{
    if (!stockPriceHistory.size())
    {
        std::cout << "Warning: No stock price data available to calculate the simple average. Please ensure the history is populated." << std::endl;
    }
    double simpleAverageSum = 0;
    for (StockPriceHistoryEntry &entry : stockPriceHistory)
    {
        double simpleAverage = (entry.openPrice + entry.highPrice + entry.lowPrice + entry.closePrice) / 4;
        simpleAverageSum += simpleAverage;
    }
    return simpleAverageSum / stockPriceHistory.size();
}

int main()
{
    std::ifstream csvFile{"AMZN.csv"};
    if (!csvFile.is_open())
    {
        std::cerr << "Could not open file " << std::endl;
        return EXIT_FAILURE;
    }

    std::string line;
    std::getline(csvFile, line);

    std::vector<StockPriceHistoryEntry> stockPriceHistory{};
    unsigned int totalCsvHistoryEntries = 0;
    while (std::getline(csvFile, line))
    {
        totalCsvHistoryEntries++;
        std::vector<std::string> tokens = tokenize(line, ',');
        if (tokens.size() != 8)
        {
            std::cerr << "The CSV line for a stock price history entry is malformed: expected 8 fields, but found "
                      << tokens.size() << ", CSV line: " << line << "." << std::endl;
            continue;
        }
        try
        {
            StockPriceHistoryEntry entry{
                tokens[0],
                std::stod(tokens[1]),
                std::stod(tokens[2]),
                std::stod(tokens[3]),
                std::stod(tokens[4]),
                std::stod(tokens[5]),
                std::stod(tokens[6]),
                std::stod(tokens[7])};
            stockPriceHistory.push_back(entry);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error parsing CSV line for stock price history: " << e.what() << ", CSV line: " << line << "." << std::endl;
            continue;
        }
    }
    std::cout << "Successfully parsed " << stockPriceHistory.size() << " out of the " << totalCsvHistoryEntries << " stock price history entries." << std::endl;

    double simpleAverageStockPrice = calculateSimpleAverageStockPrice(stockPriceHistory);
    std::cout << "The simple average stock price: " << simpleAverageStockPrice << "." << std::endl;

    csvFile.close();
    return EXIT_SUCCESS;
}
