#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using EnergyMatrix = std::vector<std::vector<uint16_t>>;
using EnergyLine = EnergyMatrix::value_type;

const std::vector<std::pair<size_t, size_t>> adjacencies = {{{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}}};

EnergyMatrix ReadInput(std::string i_file)
{
    EnergyMatrix result;
    std::fstream input(i_file);
    std::string line;
    while (input >> line)
    {
        EnergyLine& lastLine = result.emplace_back();
        for(char c : line)
        {
            lastLine.emplace_back(c - '0');
        }
    }
    return result;
}

uint32_t Flash(EnergyMatrix& i_matrix, std::vector<std::vector<bool>>& i_flashedOctopus, size_t i_x, size_t i_y)
{
    uint32_t numberOfFlashes = 1;
    i_matrix[i_x][i_y] = 0;
    i_flashedOctopus[i_x][i_y] = true;
    for(const auto& [deltax, deltay] : adjacencies)
    {
        size_t x = i_x + deltax;
        size_t y = i_y + deltay;
        if (x >= 0 && x < i_matrix.size() && y >= 0 && y < i_matrix[0].size() && !i_flashedOctopus[x][y])
        {
            i_matrix[x][y]++;
            if (i_matrix[x][y] > 9)
            {
                numberOfFlashes += Flash(i_matrix, i_flashedOctopus, x, y);
            }
        }
    }
    return numberOfFlashes;
}

uint32_t UpdateEnergyMatrix(EnergyMatrix& i_matrix)
{
    std::vector<std::vector<bool>> flashedOctopuses(i_matrix.size(), std::vector<bool>(i_matrix[0].size(), false));
    uint32_t numberOfFlashes = 0;
    for(size_t x = 0; x < i_matrix.size(); ++x)
    {
        for (size_t y = 0; y < i_matrix[0].size(); ++y)
        {
            if (!flashedOctopuses[x][y])
            {
                i_matrix[x][y]++;
                if (i_matrix[x][y] > 9)
                {
                    numberOfFlashes += Flash(i_matrix, flashedOctopuses, x, y);
                }
            }   
        }
    }
    return numberOfFlashes;
}

void PrintMatrix(const EnergyMatrix& i_matrix)
{
    for(size_t x = 0; x < i_matrix.size(); ++x)
    {
        for (size_t y = 0; y < i_matrix[0].size(); ++y)
        {
            std::cout << i_matrix[x][y];
        }
        std::cout << "\n";
    }
}

int main(int argc, char** i_argv)
{
    EnergyMatrix octopusEnergies = ReadInput("input.txt");
    const uint32_t totalNumberOfFlashes = octopusEnergies.size() * octopusEnergies[0].size();
    uint32_t step = 0;
    uint32_t numberOfFlashes = 0;
    do
    {
        numberOfFlashes = UpdateEnergyMatrix(octopusEnergies);
        step++;
    } while(numberOfFlashes < totalNumberOfFlashes);
    PrintMatrix(octopusEnergies);
    std::cout << "There have beeen [" << step << "] steps\n";
}