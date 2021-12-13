#include <iostream>
#include <fstream>

int main()
{
    std::ifstream input("input.txt");
    int firstNumber;
    int secondNumber;
    int thirdNumber;
    input >> firstNumber >> secondNumber >> thirdNumber;
    int lastSum = firstNumber + secondNumber + thirdNumber;
    int result = 0;
    int newNumber;
    while (input >> newNumber)
    {
        firstNumber = secondNumber;
        secondNumber = thirdNumber;
        thirdNumber = newNumber;
        int newSum = firstNumber + secondNumber + thirdNumber;
        if (newSum > lastSum)
        {
            result++;
        }
        lastSum = newSum;
    }
    std::cout << result;
}