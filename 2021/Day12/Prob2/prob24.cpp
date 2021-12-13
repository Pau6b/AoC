#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <functional>

struct Node
{
    std::string content;
    bool isBigCave;
    uint32_t timesVisited = 0;
    std::vector<std::reference_wrapper<Node>> links;

    Node(std::string i_content)
        : content(i_content)
        , isBigCave(std::isupper(i_content[0]))
    {
    }
    
};

std::unordered_map<std::string, Node> ReadInput(std::string i_file)
{
    std::fstream input(i_file);
    std::string line;
    std::unordered_map<std::string, Node> nodes;
    while(input >> line)
    {
        std::stringstream sstream(line);
        std::string startNodeStr;
        std::string endNodeStr;
        std::getline(sstream,startNodeStr,'-');
        std::getline(sstream,endNodeStr,'-');
        if(auto it = nodes.find(startNodeStr); it == std::end(nodes))
        {
            nodes.emplace(startNodeStr,Node(startNodeStr));
        }
        if(auto it = nodes.find(endNodeStr); it == std::end(nodes))
        {
            nodes.emplace(endNodeStr,Node(endNodeStr));
        }
        Node& startNode = nodes.at(startNodeStr);
        Node& endNode = nodes.at(endNodeStr);
        startNode.links.emplace_back(endNode);
        endNode.links.emplace_back(startNode);
    }
    return nodes;
}

uint32_t GetNumberOfPaths(Node& i_node, bool i_hasTwiceNode)
{
    if (i_node.content == "end")
    {
        return 1;
    }
    uint32_t paths = 0;
    i_node.timesVisited++;
    bool hasTwiceVisitedNode = i_hasTwiceNode || (!i_node.isBigCave && i_node.timesVisited > 1);
    for(Node& nextNode : i_node.links)
    {
        if (nextNode.content != "start" && (nextNode.isBigCave || !nextNode.isBigCave && ((hasTwiceVisitedNode && nextNode.timesVisited < 1) || (!hasTwiceVisitedNode && nextNode.timesVisited < 2))))
        {
            paths += GetNumberOfPaths(nextNode, hasTwiceVisitedNode);
        }
    }
    i_node.timesVisited--;
    return paths;
}

int main()
{
    std::unordered_map<std::string, Node> nodes = ReadInput("input.txt");
    const uint32_t numberOfPaths = GetNumberOfPaths(nodes.at("start"), false);
    std::cout << "There are [" << numberOfPaths << "] number of paths \n";
}