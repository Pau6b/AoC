#include <iostream>
#include <fstream>
#include <unordered_set>

int main()
{
    std::fstream input("input.txt");
    uint32_t result = 0;
    std::unordered_set<uint32_t> targetSizes = {2,7,3,4};
    std::string numberStr;
    while (input >> numberStr)
    {
        for (uint32_t i = 0; i < 9; ++i)
        {
            input >> numberStr;
        }
        input >> numberStr;
        std::cout << numberStr;
        for (uint32_t i = 0; i < 4; ++i)
        {
            input >> numberStr;
            if (targetSizes.find(numberStr.size()) != std::end(targetSizes))
            {
                ++result;
            }
        }
    }
    std:: cout << "\nresult is: " << result << "\n";
}