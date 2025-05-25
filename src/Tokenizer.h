#pragma once

#include <string>
#include <vector>

class Tokenizer {
public:
    std::vector<std::string> tokenize(std::string csv, char separator) const;
};
