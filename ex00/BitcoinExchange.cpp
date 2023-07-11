#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
    _database = storeDataCsv();
}

BitcoinExchange::BitcoinExchange(std::string filename)
{
    _database = storeDataCsv();
    storeInputFile(filename);
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &B)
{
    *this = B;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &B)
{
    _database = B._database;
    _input = B._input;
    return *this;
}

std::map<std::string, float> BitcoinExchange::storeDataCsv(void)
{
    std::string datafile = DATA_CSV;
    std::ifstream file;
    std::string line;
    std::map<std::string, float> data;
    size_t pos;
    file.open(datafile.c_str());
    if (!file)
        std::cerr << "Can't find data.csv in application folder" << std::endl;
    else
    {
        while (file >> line)
        {
            if (line == "date,exchange_rate")
                continue;
            else
            {
                pos = line.find(',');
                data[line.substr(0, pos)] = atof(line.substr(pos + 1).c_str());
            }
        }
        file.close();
    }
    return data;
}

void BitcoinExchange::storeInputFile(std::string filename)
{
    std::ifstream file;
    std::string line;

    file.open(filename.c_str());
    if (!file)
        std::cerr << "Error: could not open file." << std::endl;
    else
    {
        while (getline(file, line))
            _input.append(line + "\n");
        file.close();
    }
}

bool BitcoinExchange::isValidDate(std::string input)
{
    if (input.length() != 10)
        return false;

    std::stringstream ss(input);
    int year, month, day;
    char delimiter1, delimiter2;
    int daysInMonth = 31;

    if (!(ss >> year >> delimiter1 >> month >> delimiter2 >> day) || delimiter1 != '-' || delimiter2 != '-')
        return false;
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    if (month == 4 || month == 6 || month == 9 || month == 11)
        daysInMonth = 30;
    else if (month == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            daysInMonth = 29;
        else
            daysInMonth = 28;
    }

    if (day > daysInMonth)
        return false;
    return true;
}

bool BitcoinExchange::isValidValue(std::string input)
{
    if (input.empty())
        return false;

    std::istringstream iss(input);
    float value;
    iss >> value;

    if (iss.fail() || !iss.eof())
        return false;

    if (value >= 0 && value <= 1000)
        return true;
    else if (value == static_cast<int>(value) && value >= 0)
        return true;
    else
        return false;
}

bool BitcoinExchange::isValidDelimiter(char delim)
{
    if (delim != '|')
        return false;
    return true;
}

float BitcoinExchange::findMultiplier(std::string date)
{
    std::map<std::string, float>::iterator it = _database.begin();
    while (it != _database.end())
    {
        if (strcmp(date.c_str(), it->first.c_str()) == 0)
            return (it->second);
        else if (strcmp(date.c_str(), it->first.c_str()) < 0)
            return ((it--)->second);
        it++;
    }
    return _database.rbegin()->second;
}

std::string BitcoinExchange::valueError(std::string value)
{
    float nbr_value = atol(value.c_str());
    if (nbr_value != static_cast<int>(nbr_value))
        return ("too large a number.");
    else if (nbr_value < 0)
        return ("not a positive number.");
    return value;
}

void BitcoinExchange::perform(void)
{
    if (_database.empty() || _input.empty())
        return;
    std::istringstream iss(_input);
    std::string line, date, value;
    char delim;
    while (getline(iss, line))
    {
        std::stringstream ss(line);
        if (line == "date | value")
            continue;
        else if (!(ss >> date >> delim >> value))
            std::cerr << "Error: bad input => " << line << std::endl;
        else if (!isValidDate(date))
            std::cerr << "Error: invalid date => " << date << std::endl;
        else if (!isValidDelimiter(delim))
            std::cerr << "Error: invalid delimiter => " << delim << std::endl;
        else if (!isValidValue(value))
            std::cerr << "Error: " << valueError(value) << std::endl;
        else
            std::cout << date << " => " << value << " = " << (atol(value.c_str()) * findMultiplier(date)) << std::endl;
    }
}