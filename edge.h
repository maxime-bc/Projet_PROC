#ifndef EDGE_H
#define EDGE_H

typedef struct Edge Edge;
struct Edge {
    std::string source = "";
    std::string dest = "";
    float xPos = 0;
    float yPos = 0;
    std::string label = "";
    std::string color = "black";
    std::string path = "";
};

void createEdgeWithPositions(char *source, char *dest, char *label, float xPos, float yPos);

void createEdge(char *source, char *dest, char *label);

void removeEdge(char *source, char *dest);

void removeEdgesContainingNode(const std::string &nodeId);

void printEdges();

void setEdgeColor(char *color);

void setPath(char *path);

#endif //EDGE_H
