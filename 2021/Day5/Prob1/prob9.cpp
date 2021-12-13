#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class LineMap
{
public:
    void AddLine(std::pair<uint32_t, uint32_t> p1, std::pair<uint32_t, uint32_t> p2)
    {
        //std::cout << "----------------------\n";
        //std::cout <<  p1.first << " - " << p1.second << " --- " << p2.first << "-" << p2.second << "\n";
        if (p1.first != p2.first && p1.second == p2.second)
        {
            for (uint32_t i = std::min(p1.first, p2.first); i <= std::max(p1.first, p2.first); ++i)
            {
                m_map[i][p1.second]++;
                if (m_map[i][p1.second] == 2)
                {
                    m_numberOfCoincidences++;
                }
            }
        }
        else if (p1.first == p2.first && p1.second != p2.second)
        {
            for (uint32_t i = std::min(p1.second, p2.second); i <= std::max(p1.second, p2.second); ++i)
            {
                m_map[p1.first][i]++;
                if (m_map[p1.first][i] == 2)
                {
                    m_numberOfCoincidences++;
                }
            }
        }
        else
        {
            std::cout << "ignored\n";
        }
        //Print();
        //std::cout << "----------------------\n";
    }

    uint32_t GetNumberOfCoincidences() const
    {
        return m_numberOfCoincidences;
    }

    void Print() const
    {
        for (size_t i = 0; i < m_map.size(); ++i)
        {
            for (size_t j = 0; j < m_map[0].size(); ++j)
            {
                if (m_map[j][i] == 0)
                {
                    std::cout << ".";
                }
                else
                {
                    std::cout << m_map[j][i];
                }
            }
            std::cout << "\n";
        }
    }

private:
std::vector<std::vector<uint32_t>> m_map = std::vector<std::vector<uint32_t>>(1000, std::vector<uint32_t>(1000,0));
uint64_t m_numberOfCoincidences = 0;
};

int main()
{
    std::fstream input("input.txt");
    std::string line;
    LineMap map;
    while(std::getline(input, line))
    {
        uint32_t x1, y1, x2, y2;
        std::istringstream stream(line);
        stream >> x1;
        stream.get();
        stream >> y1;
        stream.get();
        stream.get();
        stream.get();
        stream.get();
        stream >> x2;
        stream.get();
        stream >> y2;
        map.AddLine({x1,y1}, {x2,y2});
    }
    std::cout << "Result is: " << map.GetNumberOfCoincidences() << std::endl;
}