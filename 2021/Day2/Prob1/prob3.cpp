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
    while (input >> command >> distance)
    {
        if (command == k_upCommand)
        {
            y -= distance;
        }
        else if (command == k_downCommand)
        {
            y += distance;
        }
        else if (command == k_forwardCommand)
        {
            x += distance;
        }
    }
    std::cout << "x is:      [" << x << "]\n";
    std::cout << "y is:      [" << y << "]\n";
    std::cout << "result is: [" << x*y << "]\n"; 
}