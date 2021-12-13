#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using FloorsVisited = std::vector<std::vector<bool>>;
using Floor = std::vector<std::string>;

size_t DFS(FloorsVisited &i_floorsVisited, const Floor &i_floors, size_t i, size_t j)
{
    if (i_floorsVisited[i][j] || i_floors[i][j] == '9')
    {
        return 0;
    }
    size_t result = 1;
    i_floorsVisited[i][j] = true;
    if (i > 0 && i_floors[i - 1][j] > i_floors[i][j])
    {
        result += DFS(i_floorsVisited, i_floors, i-1, j);
    }
    if (i < i_floors.size() - 1 && i_floors[i + 1][j] > i_floors[i][j])
    {
        result += DFS(i_floorsVisited, i_floors, i+1, j);
    }
    if (j > 0 && i_floors[i][j-1] > i_floors[i][j])
    {
        result += DFS(i_floorsVisited, i_floors, i, j-1);
    }
    if (j < i_floors[0].size() - 1 && i_floors[i][j+1] > i_floors[i][j])
    {
        result += DFS(i_floorsVisited, i_floors, i, j+1);
    }
    return result;
}

int main()
{
    std::fstream input("input.txt");
    Floor seaMap;
    FloorsVisited visitedFloors;
    {
        std::string line = "";
        while (input >> line)
        {
            seaMap.emplace_back(line);
            visitedFloors.emplace_back(std::vector<bool>(line.size(), false));
        }
    }
    std::vector<size_t> basins;
    for (size_t i = 0; i < seaMap.size(); ++i)
    {
        for (size_t j = 0; j < seaMap[0].size(); ++j)
        {
            bool meetsConditions = true;
            if (i > 0)
            {
                meetsConditions = meetsConditions && seaMap[i - 1][j] > seaMap[i][j];
            }
            if (i < seaMap.size() - 1)
            {
                meetsConditions = meetsConditions && seaMap[i + 1][j] > seaMap[i][j];
            }
            if (j > 0)
            {
                meetsConditions = meetsConditions && seaMap[i][j - 1] > seaMap[i][j];
            }
            if (j < seaMap[0].size() - 1)
            {
                meetsConditions = meetsConditions && seaMap[i][j + 1] > seaMap[i][j];
            }
            if (meetsConditions)
            {
                basins.emplace_back(DFS(visitedFloors, seaMap, i, j));
            }
        }
    }
    std::sort(std::rbegin(basins), std::rend(basins));
    size_t result = basins[0] * basins[1] * basins[2];
    std::cout << "basins are: [" << basins[0] << "] [" << basins[1] << "] [" << basins[2] << "]\n";
    std::cout << "result is: " << result << "\n";
}
