#include <iostream>
#include <fstream>
#include <array>
#include <cmath>

constexpr size_t nbits = 12;

int main() {
    std::ifstream input("input.txt");
    std::array<size_t, nbits> oneBits{};
    std::string bits;
    size_t numberCount = 0;
    while(input >> bits)
    {
        ++numberCount;
        for (size_t i = 0; i < nbits; ++i)
        {
            if (bits[i] == '1')
            {
                ++oneBits[i];
            }
        }
    }
    size_t finalNumber = 0;
    for (size_t number : oneBits)
    {
        std::cout << "zeros: [" << numberCount-number << "] -- ones: [" << number << "]\n";
        finalNumber <<= 1;
        if (number > (numberCount-number))
        {
            finalNumber = (finalNumber | 1);
        }
    }
    size_t maxNumber = std::pow(2,nbits)-1;
    size_t reverseNumber = maxNumber - finalNumber;
    std::cout << "Number of maximums: [" << finalNumber << "]\n";
    std::cout << "Number of minimums: [" << reverseNumber << "]\n";
    std::cout << "max number is:      [" << maxNumber << "]\n";
    std::cout << "Result is: " << finalNumber * reverseNumber;
}