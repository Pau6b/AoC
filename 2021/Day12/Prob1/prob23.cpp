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
    bool isVisited = false;
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

uint32_t GetNumberOfPaths(Node& i_node, std::vector<std::string> i_paths)
{
    if (i_node.content == "end")
    {
        //for (const auto& content: i_paths)
        //{
        //    std::cout << content << ",";
        //}
        //std::cout << "end\n";
        return 1;
    }
    i_paths.emplace_back(i_node.content);
    uint32_t paths = 0;
    i_node.isVisited = true;
    for(Node& nextNode : i_node.links)
    {
        if(nextNode.isBigCave || !nextNode.isBigCave && !nextNode.isVisited)
        {
            paths += GetNumberOfPaths(nextNode, i_paths);
        }
    }
    i_node.isVisited = false;
    return paths;
}

int main()
{
    std::unordered_map<std::string, Node> nodes = ReadInput("input.txt");
    const uint32_t numberOfPaths = GetNumberOfPaths(nodes.at("start"), {});
    std::cout << "There are [" << numberOfPaths << "] number of paths \n";
}