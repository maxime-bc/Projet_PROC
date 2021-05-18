#ifndef EDGE_H
#define EDGE_H

typedef struct Edge Edge;
struct Edge {
    std::string source;
    std::string dest;
    float xPos = 0;
    float yPos = 0;
    std::string label;
    std::string color = "black";
    std::string path;
};

void createEdgeWithPosition(const std::string &source, const std::string &dest, const std::string &label, float xPos,
                            float yPos);

void createEdge(const std::string &source, const std::string &dest, const std::string &label);

void removeEdge(const std::string &source, const std::string &dest);

void removeEdgesContainingNode(const std::string &nodeId);

void renameEdgeNode(const std::string &currentNodeId, const std::string &newNodeId);

void printEdges();

void setEdgeColor(const std::string &color);

void setPath(const std::string &path);

#endif //EDGE_H
