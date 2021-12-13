#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>

struct Point
{
    uint32_t x;
    uint32_t y;

    bool operator<(const Point& i_other) const
    {
        if (x == i_other.x)
        {
            return y < i_other.y;
        }
        return x < i_other.x;
    }
};

enum class Direction
{
    X,
    Y
};

struct Action
{
    uint32_t lineToFold;
    Direction direction;
};

std::pair<std::set<Point>, std::vector<Action>> ReadInput(std::string i_file)
{
    std::fstream input(i_file);
    std::stringstream buffer;
    buffer << input.rdbuf();
    std::string line;
    std::set<Point> points;
    std::getline(buffer,line,'\n');
    while (line != "")
    {
        std::stringstream sstream(line);
        std::string x;
        std::string y;
        std::getline(sstream, y, ',');
        std::getline(sstream, x, ',');
        points.emplace(Point{std::stoul(x), std::stoul(y)});
        std::getline(buffer,line,'\n');
    }
    std::vector<Action> actions;
    while(std::getline(buffer,line,'\n'))
    {
        std::stringstream sstream(line);
        std::getline(sstream,line,' ');
        std::getline(sstream,line,' ');
        char dir;
        sstream >> dir;
        char ignore;
        sstream >> ignore;
        uint32_t lineToFold;
        sstream >> lineToFold;
        actions.emplace_back(Action{lineToFold, dir == 'x' ? Direction::X : Direction::Y});
    }
    return {points,actions};
}

Point CalculateResultingPoint(const Point& i_point, const Action& i_action)
{
    auto coordinateCalculator = [](const uint32_t& i_coordinate, const uint32_t& i_line) -> uint32_t{
        if (i_coordinate < i_line)
        {
            return i_coordinate;
        }
        else
        {
            uint32_t distance = i_coordinate - i_line;
            return i_line - distance;
        }
    };
    switch (i_action.direction)
    {
    case Direction::Y:
    {
        return Point{coordinateCalculator(i_point.x, i_action.lineToFold), i_point.y};
    }
    break;
    case Direction::X:
    {
        return Point{i_point.x, coordinateCalculator(i_point.y, i_action.lineToFold)};
    }
    break;
    }
}

std::set<Point> ApplyAction(const std::set<Point>& i_points, const Action& i_action)
{
    std::set<Point> result;
    for (const Point& p : i_points)
    {
        result.emplace(CalculateResultingPoint(p, i_action));
    }
    return result;
}

void PrintPoints(const std::set<Point>& i_points)
{
    std::cout << "----------\nPrinting points\n";
    for (const Point& p : i_points)
    {
        std::cout << "x: [" << p.x << "], y: [" << p.y << "]\n";
    }
    std::cout << "----------\n";
}

int main() {
    auto [points, actions] = ReadInput("input.txt");
    //PrintPoints(points);
    //for (const auto& action : actions)
    //{
        points = ApplyAction(points, actions[0]);
//
    //    std::string dir = action.direction == Direction::X ? "x" : "y";
    //    std::cout << "action direction: [" <<  dir << "], line: [" << action.lineToFold << "]\n";
    //    PrintPoints(points);
    //}
    std::cout << "result is: " << points.size() << "\n";
}