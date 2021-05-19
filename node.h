#ifndef NODE_H
#define NODE_H

#include <list>
#include <string>

class Node { //TODO: change class, needs initial and final attribute
public:
    std::string id;
    float xPos = 0;
    float yPos = 0;
    std::string label;
    std::string color;
    std::string backgroundColor;
    float size = -1;
    std::string initial;
    std::string final;
};

extern std::list<Node> NODES;

void createNode(const std::string &nodeId, float xPos, float yPos);

void removeNode(const std::string &nodeId);

bool nodeExists(const std::string &nodeId);

void renameNode(const std::string &currentNodeId, const std::string &newNodeId);

void moveAllNodes(float xPos, float yPos);

void editNode(const std::string &nodeId);

void moveNode(const std::string &nodeId, float xPos, float yPos);

void moveMultipleNodesById(float xPos, float yPos);

void addId(const std::string &id);

void printNodes();

int getNodeIndex(const std::string &nodeId);

void setLabel(const std::string &label);

void setNodeColor(const std::string &color);

void setBackgroundColor(const std::string &backgroundColor);

void setSize(float size);

void setType(const std::string &type, const std::string &direction);

#endif //NODE_H
