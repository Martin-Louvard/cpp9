#ifndef BITCOIN_HPP
#define BITCOIN_HPP

#define DATA_CSV "data.csv"

#include <map>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <limits>
#include <cstring>

class BitcoinExchange{
    public:
        BitcoinExchange();
        BitcoinExchange(std::string filename);
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &);
        BitcoinExchange&operator=(const BitcoinExchange &);
        void perform(void);


    private:
        std::map<std::string, float> _database;
        std::string _input;
        std::map<std::string, float> storeDataCsv(void);
        void storeInputFile(std::string filename);
        bool isValidDate(std::string input);
        bool isValidValue(std::string input);
        bool isValidDelimiter(char delim);
        float findMultiplier(std::string date);
        std::string valueError(std::string value);
};
#endif