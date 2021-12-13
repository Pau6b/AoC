#include <iostream>
#include <fstream>
#include <unordered_map>
#include <utility>
#include <array>
#include <algorithm>
#include <string>

std::unordered_map<std::string, uint32_t> CreateAssociations(std::array<std::string, 10>& i_digits)
{
    std::sort(std::begin(i_digits), std::end(i_digits), [](const auto& i_lhs, const auto& i_rhs){return i_lhs.size() < i_rhs.size();});
    for (std::string& str : i_digits)
    {
        std::sort(std::begin(str), std::end(str));
    }
    std::unordered_map<std::string, uint32_t> result;
    result.emplace(i_digits[0], 1);
    result.emplace(i_digits[1], 7);
    result.emplace(i_digits[2], 4);
    result.emplace(i_digits[9], 8);
    char middleBar = '.';
    char leftUpBar = '.';
    uint32_t number3Index;
    //We identify the number 3
    for (uint32_t i = 3; i < 6; ++i)
    {
        const std::string currentStr = i_digits[i];
        if (currentStr.find(i_digits[0][0]) != std::string::npos && currentStr.find(i_digits[0][1]) != std::string::npos)
        {
            result.emplace(currentStr, 3);
            number3Index = i;
            for(const char& ch : i_digits[2])
            {
                if (currentStr.find(ch) == std::string::npos)
                {
                    leftUpBar = ch;
                }
            }
            for(const char& ch : i_digits[2])
            {
                if (i_digits[0].find(ch) == std::string::npos && ch != leftUpBar)
                {
                    middleBar = ch;
                }
            }
        }
    }
    //We identify numbers 2 and 5
    for (uint32_t i = 3; i < 6; ++i)
    {
        const std::string currentStr = i_digits[i];
        if (i != number3Index )
        {
            if (currentStr.find(leftUpBar) == std::string::npos)
            {
                result.emplace(currentStr, 2);
            }  
            else
            {
                result.emplace(currentStr, 5);
            }
        }

    }
    //We identify 0, 6, 9
    for (uint32_t i = 6; i < 9; ++i)
    {
        const std::string currentStr = i_digits[i];
        //0 does not have a middle bar
        if (currentStr.find(middleBar) == std::string::npos)
        {
            result.emplace(currentStr,0);
        }
        //9 has number one in it
        else if (currentStr.find(i_digits[0][0]) != std::string::npos && currentStr.find(i_digits[0][1]) != std::string::npos)
        {
            result.emplace(currentStr, 9);
        }
        //Else it is a 6
        else
        {
            result.emplace(currentStr, 6);
        }
    }
    return result;
}

int main()
{
    std::fstream input("input.txt");
    uint32_t result = 0;
    std::string numberStr;
    while (input >> numberStr)
    {
        std::array<std::string, 10> digits;
        digits[0] = numberStr;
        for (uint32_t i = 1; i < 10; ++i)
        {
            input >> digits[i];
        }
        input >> numberStr;

        std::unordered_map<std::string, uint32_t> digitsToNumbersMap = CreateAssociations(digits);

        uint32_t resultingNumber = 0;
        for (uint32_t i = 0; i < 4; ++i)
        {
            input >> numberStr;
            resultingNumber *= 10;
            std::sort(std::begin(numberStr), std::end(numberStr));
            auto it = digitsToNumbersMap.find(numberStr);
            if (it != std::end(digitsToNumbersMap))
            {
                resultingNumber += it->second;
            }
            else
            {
                std::cout << "error on string: " << numberStr << "\n";
            }
        }
        result += resultingNumber;
    }
    std:: cout << "\nresult is: " << result << "\n";
}