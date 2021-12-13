#include <iostream>
#include <fstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <optional>

const std::unordered_map<char, uint32_t> illegalCharacterTable = {{
    {')', 3},
    {']', 57},
    {'}', 1197},
    {'>', 25137},
}};

const std::unordered_map<char, char> characterMatchTable = {{
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
    uint32_t result = 0;
    while(input >> line)
    {
        std::stack<char> currentUnmatchedChars;
        std::optional<char> illegalChar = std::nullopt;
        for(char c : line)
        {
            if (openingChars.find(c) != std::end(openingChars))
            {
                currentUnmatchedChars.emplace(c);
            }
            else
            {
                const char respectiveOpeningChar = characterMatchTable.at(c);
                if (currentUnmatchedChars.top() == respectiveOpeningChar)
                {
                    currentUnmatchedChars.pop();
                }
                else
                {
                    //std::cout << "Illegal matching char found : " << c << "\n";
                    illegalChar = c;
                    break;
                }
            }
        }
        if (illegalChar.has_value())
        {
            result += illegalCharacterTable.at(illegalChar.value());
        }
    }
    std::cout << "result is: " << result << "\n";
}