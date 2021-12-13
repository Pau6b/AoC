#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

class Board
{
public:
    Board(const std::vector<std::vector<uint32_t>>& i_numbers)
        : m_numbers(i_numbers)
        , m_calledNumbers(i_numbers.size(), std::vector(i_numbers[0].size(), false))
        , m_transposedCalledNumbers(i_numbers.size(), std::vector(i_numbers[0].size(), false))
    {}

    void OnNumberCalled(uint32_t i_number)
    {
        bool found = false;
        for (size_t i = 0; i < m_numbers.size() && !found; ++i)
        {
            for (size_t j = 0; j < m_numbers[0].size() && !found; ++j)
            {
                if (m_numbers[i][j] == i_number)
                {
                    found = true;
                    m_calledNumbers[i][j] = true;
                    m_transposedCalledNumbers[j][i] = true;
                }
            }
        }
        m_lastCalledNumber = i_number;
    }

    bool HasWon()
    {
        return std::any_of(std::begin(m_calledNumbers), std::end(m_calledNumbers), [](const std::vector<bool>& i_numbers){return std::all_of(std::begin(i_numbers),std::end(i_numbers), [](bool i_number){return i_number;});})
         ||std::any_of(std::begin(m_transposedCalledNumbers), std::end(m_transposedCalledNumbers), [](const std::vector<bool>& i_numbers){return std::all_of(std::begin(i_numbers),std::end(i_numbers), [](bool i_number){return i_number;});});
    }

    int32_t GetResult()
    {
        uint32_t result = 0;
        for (size_t i = 0; i < m_numbers.size(); ++i)
        {
            for (size_t j = 0; j < m_numbers[0].size(); ++j)
            {
                if (!m_calledNumbers[i][j])
                {
                    result += m_numbers[i][j];
                }
            }
        }
        return result * m_lastCalledNumber;
    }

private:
    const std::vector<std::vector<uint32_t>> m_numbers;
    std::vector<std::vector<bool>> m_calledNumbers;
    std::vector<std::vector<bool>> m_transposedCalledNumbers;
    int32_t m_lastCalledNumber = -1;
};

std::vector<uint32_t> ParseNumbers(std::string i_numbers)
{
    std::vector<uint32_t> result;
    std::istringstream stream(i_numbers);
    std::string number;
    while (std::getline(stream, number, ','))
    {
        result.push_back(std::stoi(number));
    }
    
    return result;
}

int main() 
{
    std::fstream input("input.txt");
    std::string numbersStr;
    std::getline(input, numbersStr);
    std::vector<uint32_t> numbersToCall = ParseNumbers(numbersStr);
    std::vector<Board> boards;
    std::string line;
    while (getline(input, line))
    {
        std::vector<std::vector<uint32_t>> numbers(5, std::vector(5, uint32_t(0)));
        uint32_t currentNumber;
        for (uint32_t i = 0; i < 5; ++i)
        {
            for (uint32_t j = 0; j < 5; ++j)
            {
                input >> currentNumber;
                numbers[i][j] = currentNumber;
            }
        }
        boards.emplace_back(numbers);
    }

    bool hasFinished = false;
    for (auto number : numbersToCall)
    {
        for (auto& board : boards)
        {
            board.OnNumberCalled(number);
            if (board.HasWon())
            {
                std::cout << "Result is: " << board.GetResult() << "\n";
                hasFinished = true;
                break;
            }
        }
        if (hasFinished)
        {
            break;
        }
    }
}