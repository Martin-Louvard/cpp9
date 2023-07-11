#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        std::cerr << "Error: Missing arguments" << std::endl;
        return 1;
    }

    try
    {
        RPN r(argc, argv);    
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}