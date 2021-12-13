#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main()
{
    std::fstream input("input.txt");
    std::vector<std::string> seaMap;
    {
        std::string line = "";
        while (input >> line)
        {
            seaMap.emplace_back(line);
        }
    }

    size_t result = 0;
    for (size_t i = 0; i < seaMap.size(); ++i)
    {
        for (size_t j = 0; j < seaMap[0].size(); ++j)
        {
            bool meetsConditions = true;
            if (i > 0)
            {
                meetsConditions = meetsConditions && seaMap[i-1][j] > seaMap[i][j];
            }
            if (i < seaMap.size()-1)
            {
                meetsConditions = meetsConditions && seaMap[i+1][j] > seaMap[i][j];
            }
            if (j > 0)
            {
                meetsConditions = meetsConditions && seaMap[i][j-1] > seaMap[i][j];
            }
            if (j < seaMap[0].size()-1)
            {
                meetsConditions = meetsConditions && seaMap[i][j+1] > seaMap[i][j];
            }
            if (meetsConditions)
            {
                //std::cout << "number found! [" << seaMap[i][j] << "]\n";
                result += seaMap[i][j] - '0' + 1;
            }
        }
    }
    std::cout << "result is: " << result << "\n";
}
