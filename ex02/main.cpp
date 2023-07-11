#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        std::cerr << "Error: arguments required" << std::endl;
        return (1);
    }
    try
    {
        PmergeMe p(argc, argv);
    }
    catch(const PmergeMe::Error& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}