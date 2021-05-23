#ifndef EDGE_H
#define EDGE_H

#include <list>

class Edge {
public:
    std::string source;
    std::string dest;
    float xPos = 0;
    float yPos = 0;
    std::string label;
    std::string color = "black";
    std::string path;
};

extern std::list<Edge> EDGES;

void createEdgeWithPosition(const std::string &source, const std::string &dest, const std::string &label, float xPos,
                            float yPos);

void createEdge(const std::string &source, const std::string &dest, const std::string &label);

void removeEdge(const std::string &source, const std::string &dest);

void removeEdgesContainingNode(const std::string &nodeId);

int getEdgeIndex(const std::string &source, const std::string &dest);

void editEdge(const std::string &source, const std::string &dest);

void renameEdgeNode(const std::string &currentNodeId, const std::string &newNodeId);

void printEdges();

void setEdgeColor(const std::string &color);

void setPath(const std::string &path);

#endif //EDGE_H
