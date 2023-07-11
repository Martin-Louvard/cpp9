#include "BitcoinExchange.hpp"
#include <iostream>

int main(int ac, char**argv)
{
    if (ac != 2)
    {
        std::cerr << "Error: could not open file" << std::endl;
        return(1);
    }

    BitcoinExchange b(argv[1]);
    b.perform();
    
    return 0;
}