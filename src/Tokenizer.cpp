#include "Tokenizer.h"
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> Tokenizer::tokenize(std::string csv, char separator) const {
    std::vector<std::string> tokens{};

    if (!csv.length()) {
        return tokens;
    }

    signed int start = 0;
    signed int end = start;

    do {
        end = csv.find_first_of(separator, start);
        if (end >= 0) {
            tokens.push_back(csv.substr(start, end - start));
        } else {
            tokens.push_back(csv.substr(start, csv.length() - start));
        }
        start = end + 1;
    } while (end >= 0);

    return tokens;
}