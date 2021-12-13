#include <iostream>
#include <fstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <algorithm>

const std::unordered_map<char, uint32_t> completeCharPoints = {{
    {'(', 1},
    {'[', 2},
    {'{', 3},
    {'<', 4},
}};

const std::unordered_map<char, char> characterMatchTable = {{
    {'[',']'},
    {'(',')'},
    {'{','}'},
    {'<','>'}
}};

const std::unordered_map<char, char> reverseCharacterMatchTable = {{
    {']','['},
    {')','('},
    {'}','{'},
    {'>','<'}
}};

const std::unordered_set<char> openingChars = {{'(', '[', '{', '<'}};

int main()
{
    std::fstream input("input.txt");
    std::string line;
    std::vector<uint64_t> results;
    while(input >> line)
    {
        std::stack<char> currentUnmatchedChars;
        bool isLineCorrect = true;
        for(char c : line)
        {
            if (openingChars.find(c) != std::end(openingChars))
            {
                currentUnmatchedChars.emplace(c);
            }
            else
            {
                const char respectiveOpeningChar = reverseCharacterMatchTable.at(c);
                if (currentUnmatchedChars.top() == respectiveOpeningChar)
                {
                    currentUnmatchedChars.pop();
                }
                else
                {
                    isLineCorrect = false;
                    break;
                }
            }
        }
        if (isLineCorrect)
        {
            uint64_t partialResult = 0;
            while (!currentUnmatchedChars.empty())
            {
                const char currentChar = currentUnmatchedChars.top();
                currentUnmatchedChars.pop();
                partialResult *= 5;
                partialResult += completeCharPoints.at(currentChar);
            }
            results.emplace_back(partialResult);
        }
    }
    std::sort(std::begin(results), std::end(results));
    //for (auto result : results)
    //{
    //    std::cout << result << "\n";
    //}
    std::cout << "result is: " << results[results.size()/2] << "\n";
}