#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

int main()
{
    std::ifstream file( "input.txt" );
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string numberStr;
    std::unordered_map<uint32_t, size_t> numbers;
    uint32_t maxNumber = 0;
    size_t maxNumberRepetitions = 0;
    while (std::getline(buffer, numberStr, ','))
    {
        uint32_t number = stoi(numberStr);
        auto it = numbers.find(number);
        if (it == std::end(numbers))
        {
            numbers.emplace(number, 1);
            if (maxNumberRepetitions == 0)
            {
                maxNumber = number;
                maxNumberRepetitions = 1;
            }
        }
        else
        {
            it->second++;
            if (it->second > maxNumberRepetitions)
            {
                maxNumber = number;
                maxNumberRepetitions = it->second;
            }
        }
    }

    std::cout << "median is: " << maxNumber << " -- " << maxNumberRepetitions << "\n";
    size_t result = 0;
    for (const auto& [number, repetitions] : numbers)
    {
        const size_t difference = std::max(maxNumber, number) - std::min(maxNumber, number);
        result += (difference * repetitions);
    }
    std::cout << "result is: " << result << "\n";
    
}