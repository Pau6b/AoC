#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <cmath>
#include <string>

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
}