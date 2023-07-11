#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <exception>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <list>

#define INSERTION_THRESHOLD 16

class PmergeMe{
    public:
        PmergeMe();
        PmergeMe(int argc, char **argv);
        ~PmergeMe();
        PmergeMe(const PmergeMe &);
        PmergeMe&operator=(const PmergeMe &);

        class Error : public std::exception {
            public :
                virtual const char *what(void) const throw(){return "Error";};
        };

    private:
        void insertion_sort_vector(std::vector<int>& vec, int low, int high);
        void merge_vector(std::vector<int>& vec, int low, int mid, int high);
        void merge_insertion_sort_vector(std::vector<int>& vec, int low, int high);
        void merge_insertion_sort_list(std::list<int>& list);
        void merge_list(std::list<int>& left, std::list<int>& right, std::list<int>& list);
        std::vector<int> _to_sort_vector;
        std::list<int> _to_sort_list;
};
#endif