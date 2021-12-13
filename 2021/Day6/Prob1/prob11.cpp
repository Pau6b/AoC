#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

struct Fish
{
    uint32_t stepsToCreateFish;
    uint32_t startStep;
};

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
    std::vector<Fish> fishes;
    while(std::getline(inputStrStream, numberStr, ','))
    {
        uint32_t stepsToCreateFish = std::stoi(numberStr);
        fishes.emplace_back(Fish{stepsToCreateFish, 0});
    }
    size_t currentFish = 0;
    while(currentFish < fishes.size())
    {
        const Fish& fish = fishes[currentFish];
        ++currentFish;

        uint32_t currentStep = fish.startStep;
        currentStep += fish.stepsToCreateFish;
        if (currentStep < numberOfSteps)
        {
            fishes.emplace_back(Fish{9,currentStep});
        }
        currentStep += 7;
        for (; currentStep < numberOfSteps; currentStep += 7)
        {
            fishes.emplace_back(Fish{9, currentStep});
        }
    }
    std::cout << "Result is: " << fishes.size() << "\n";
}