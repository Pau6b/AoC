#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <sstream>
#include <numeric>

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        std::cout << "Program expects 1 argument which is the number of steps\n";
        return 0;
    }
    int32_t numberOfSteps = std::stoi(argv[1]);
    std::ifstream input("input.txt");
    std::string fullInput;
    std::getline(input,fullInput);
    std::string numberStr;
    std::istringstream inputStrStream(fullInput);
    std::array<unsigned long long, 9> fishes {};
    while(std::getline(inputStrStream, numberStr, ','))
    {
        uint32_t stepsToCreateFish = std::stoi(numberStr);
        fishes[stepsToCreateFish]++;
    }
    size_t currentDay = 0;
    while(currentDay < numberOfSteps)
    {
        const unsigned long long currentDayBirth = (currentDay % 9ULL);
        const unsigned long long nextBirthDay = (currentDayBirth+7ULL) % 9ULL;
        fishes[nextBirthDay] += fishes[currentDayBirth];
        ++currentDay;
    }
    std::cout << "Result is: " << std::accumulate<>(std::begin(fishes), std::end(fishes), 0ULL) << "\n";
}