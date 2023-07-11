#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(int argc, char **argv)
{
    int nb;
    clock_t start_time, end_time;
    double elapsed_time;

    for (int i = 1; i < argc; i++)
    {
        nb = std::atoi(argv[i]);
        if (nb <= 0)
            throw Error();
        _to_sort_vector.push_back(nb);
        _to_sort_list.push_back(nb);
    }
    std::cout << "Before : ";
    for (size_t i = 0; i < _to_sort_vector.size(); i++)
        std::cout << _to_sort_vector[i] << " ";
    start_time = clock();
    merge_insertion_sort_vector(_to_sort_vector, 0, argc - 2);
    end_time = clock();
    elapsed_time = static_cast<double>(end_time - start_time) / (CLOCKS_PER_SEC / 1000000);
    std::cout << "\nAfter : ";
    for (size_t i = 0; i < _to_sort_vector.size(); i++)
        std::cout << _to_sort_vector[i] << " ";
    std::cout << "\nTime to process a range of " << argc - 1 << " elements with std::vector : " << elapsed_time << " ms";
    start_time = clock();
    merge_insertion_sort_list(_to_sort_list);
    end_time = clock();
    elapsed_time = static_cast<double>(end_time - start_time) / (CLOCKS_PER_SEC / 1000000);
    std::cout << "\nTime to process a range of " << argc - 1 << " elements with std::list : " << elapsed_time << " ms" << std::endl;
}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &P)
{
    *this = P;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &P)
{
    _to_sort_vector = P._to_sort_vector;
    _to_sort_list = P._to_sort_list;
    return *this;
}

void PmergeMe::insertion_sort_vector(std::vector<int> &vec, int low, int high)
{
    for (int i = low + 1; i <= high; i++)
    {
        int key = vec[i];
        int j = i - 1;
        while (j >= low && vec[j] > key)
        {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = key;
    }
}

void PmergeMe::merge_vector(std::vector<int> &vec, int low, int mid, int high)
{
    std::vector<int> temp(high - low + 1);
    int i = low, j = mid + 1, k = 0;
    while (i <= mid && j <= high)
    {
        if (vec[i] <= vec[j])
        {
            temp[k++] = vec[i++];
        }
        else
        {
            temp[k++] = vec[j++];
        }
    }
    while (i <= mid)
    {
        temp[k++] = vec[i++];
    }
    while (j <= high)
    {
        temp[k++] = vec[j++];
    }
    for (int i = low; i <= high; i++)
    {
        vec[i] = temp[i - low];
    }
}

void PmergeMe::merge_insertion_sort_vector(std::vector<int> &vec, int low, int high)
{
    if (high - low + 1 <= INSERTION_THRESHOLD)
    {
        insertion_sort_vector(vec, low, high);
    }
    else
    {
        int mid = (low + high) / 2;
        merge_insertion_sort_vector(vec, low, mid);
        merge_insertion_sort_vector(vec, mid + 1, high);
        merge_vector(vec, low, mid, high);
    }
}

void PmergeMe::merge_list(std::list<int> &left, std::list<int> &right, std::list<int> &list)
{
    while (!left.empty() && !right.empty())
    {
        if (left.front() <= right.front())
        {
            list.push_back(left.front());
            left.pop_front();
        }
        else
        {
            list.push_back(right.front());
            right.pop_front();
        }
    }

    // Append the remaining elements
    while (!left.empty())
    {
        list.push_back(left.front());
        left.pop_front();
    }
    while (!right.empty())
    {
        list.push_back(right.front());
        right.pop_front();
    }
}

void PmergeMe::merge_insertion_sort_list(std::list<int> &list)
{
    if (list.size() < 2)
        return;

    std::list<int> left, right;
    std::list<int>::iterator it = list.begin();
    for (size_t i = 0; i < list.size() / 2; i++, it++)
    {
        left.push_back(*it);
    }
    for (; it != list.end(); ++it)
    {
        right.push_back(*it);
    }
    // Recursively sort the two halves
    merge_insertion_sort_list(left);
    merge_insertion_sort_list(right);

    // Merge the two sorted halves
    list.clear();
    merge_list(left, right, list);
}