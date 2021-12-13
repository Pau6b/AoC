#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <cmath>
#include <string>

uint64_t CalculateFuel(int i_avg, const std::vector<int>& i_numbers)
{
    return std::accumulate(std::begin(i_numbers), std::end(i_numbers), uint64_t(0), [i_avg](uint64_t i_acc, int i_n) {
        uint64_t steps = std::abs(static_cast<long>(i_n) - i_avg);
        uint64_t fuel = (steps * (steps+1)) / 2;
        return i_acc + fuel;
    });
}

int main()
{
    std::ifstream file( "input.txt" );
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::vector<int> numbers;
    std::string numberStr = "";
    while (std::getline(buffer, numberStr, ','))
    {
       numbers.emplace_back(stoi(numberStr));
    }
    std::sort(std::begin(numbers), std::end(numbers));
    int median = numbers[numbers.size() /2];
    int result = std::accumulate(std::begin(numbers), 
                                std::end(numbers), 
                                0, 
                                [median](int i_accumulated, int i_number){ 
                                    return i_accumulated + std::abs(i_number - median);
                                });
    std::cout << "result 1 is: " << result << "\n";

    int sum1 = std::accumulate(std::cbegin(numbers), std::cend(numbers), 0L);
    double avg1 = static_cast<double>(sum1) / numbers.size();
    int floor1 = std::floor(avg1);
    int ceiling1 = std::ceil(avg1);
    uint64_t result2 = std::min(CalculateFuel(floor1, numbers), CalculateFuel(ceiling1, numbers));
    std::cout << "result 2 is: " << result2 << "\n";

    return 0;
}