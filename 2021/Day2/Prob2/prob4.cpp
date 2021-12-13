#include <iostream>
#include <fstream>

const std::string k_upCommand = "up";
const std::string k_downCommand = "down";
const std::string k_forwardCommand = "forward";

int main()
{
    std::ifstream input("input.txt");
    std::string command;
    int distance;
    int x = 0;
    int y = 0;
    int aim = 0;
    while (input >> command >> distance)
    {
        if (command == k_upCommand)
        {
            aim -= distance;
        }
        else if (command == k_downCommand)
        {
            aim += distance;
        }
        else if (command == k_forwardCommand)
        {
            y += aim * distance;
            x += distance;
        }
        //std::cout << "command is : [" << command << "] and distance is [" << distance << "]\n";
        //std::cout << "x is:      [" << x << "]\n";
        //std::cout << "y is:      [" << y << "]\n";
        //std::cout << "aim is:    [" << aim << "]\n";
    }
    std::cout << "x is:      [" << x << "]\n";
    std::cout << "y is:      [" << y << "]\n";
    std::cout << "result is: [" << x*y << "]\n"; 
}