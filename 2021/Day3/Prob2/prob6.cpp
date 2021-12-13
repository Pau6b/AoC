#include <iostream>
#include <fstream>
#include <array>
#include <cmath>
#include <set>
#include <vector>
#include <algorithm>
#include <variant>
#include <memory>
#include <functional>

constexpr size_t nbits = 12;

bool Sorter(size_t i_lhs, size_t i_rhs, size_t i_bit)
{
    const bool lhsIsOne = (i_lhs & (1 << i_bit)) != 0;
    const bool rhsIsOne = (i_rhs & (1 << i_bit)) != 0;
    if (lhsIsOne == rhsIsOne)
    {
        return false;
    }
    return lhsIsOne; 
}

size_t GetResultNumber(std::vector<size_t>::iterator i_begin, std::vector<size_t>::iterator i_end, bool i_mostFrequent, size_t i_bit)
{
    if (std::distance(i_begin, i_end) == 1)
    {
        return *i_begin;
    }
    std::sort(i_begin, i_end, std::bind(&Sorter, std::placeholders::_1,std::placeholders::_2, i_bit));
    auto it = std::find_if(i_begin, i_end, [i_bit](size_t i_value){return (i_value & (1 << i_bit)) == 0;});
    auto ones = std::distance(i_begin, it);
    auto zeroes = std::distance(it, i_end);
    if (ones >= zeroes)
    {
        if (i_mostFrequent)
        {
            return GetResultNumber(i_begin, it, i_mostFrequent, i_bit-1);
        } 
        else
        {
            return GetResultNumber(it, i_end, i_mostFrequent, i_bit-1);
        }  
    }
    else
    {
        if (!i_mostFrequent)
        {
            return GetResultNumber(i_begin, it, i_mostFrequent, i_bit-1);
        } 
        else
        {
            return GetResultNumber(it, i_end, i_mostFrequent, i_bit-1);
        }  
    }
}

std::pair<size_t, size_t> GetResult(std::vector<size_t>::iterator i_begin, std::vector<size_t>::iterator i_end)
{
    const auto bit = nbits-1;
    std::sort(i_begin, i_end, std::bind(&Sorter, std::placeholders::_1,std::placeholders::_2, nbits-1));
    auto it = std::find_if(i_begin, i_end, [bit](size_t i_value){return (i_value & (1 << bit)) == 0;});
    auto ones = std::distance(i_begin, it);
    auto zeroes = std::distance(it, i_end);
    std::vector<size_t>::iterator mostFreqBegin;
    std::vector<size_t>::iterator mostFreqEnd;
    std::vector<size_t>::iterator leastFreqBegin;
    std::vector<size_t>::iterator leastFreqEnd;
    if (ones > zeroes)
    {
        mostFreqBegin = i_begin;
        mostFreqEnd = it;
        leastFreqBegin = it;
        leastFreqEnd = i_end;   
    }
    else
    {
        leastFreqBegin = i_begin;
        leastFreqEnd = it;
        mostFreqBegin = it;
        mostFreqEnd = i_end;  
    }
    return std::make_pair(GetResultNumber(mostFreqBegin,mostFreqEnd, true, bit-1), GetResultNumber(leastFreqBegin,leastFreqEnd, false, bit-1) );
}

int main() {
    std::ifstream input("input.txt");
    std::string bits;
    std::vector<size_t> numbers;
    while(input >> bits)
    {
        numbers.emplace_back(strtol(bits.c_str(), NULL, 2));
    }
    auto [o2, co2] = GetResult(std::begin(numbers), std::end(numbers));

    std::cout << "Number of co2: [" << co2 << "]\n";
    std::cout << "Number of o2: [" << o2 << "]\n";
    std::cout << "Result is: " << co2 * o2;
}