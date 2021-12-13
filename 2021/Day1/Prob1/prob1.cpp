#include <iostream>
#include <fstream>

int main()
{
    std::ifstream input("input.txt");
    int firstNumber = 0;
    input >> firstNumber;
    int secondNumber;
    int result = 0;
    while (input >> secondNumber)
    {
        if (secondNumber > firstNumber)
        {
            result++;
        }
        firstNumber = secondNumber;
    }
    std::cout << result;
}