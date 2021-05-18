#ifndef NODE_H
#define NODE_H

#include <list>
#include <string>

struct Node {
    std::string id = "";
    float xPos = 0;
    float yPos = 0;
    std::string label = "";
    std::string color = "black";
    std::string backgroundColor = "white";
    float size = 30;
    std::string type = "";
    std::string direction = "";
};

void createNode(const std::string& nodeId, float xPos, float yPos);

void removeNode(const std::string& id);

bool nodeExists(const std::string& nodeId);

void moveAllNodes(float xPos, float yPos);

void moveNode(const std::string &nodeId, float xPos, float yPos);

void moveMultipleNodesById(float xPos, float yPos);

void addId(const std::string &id);

void printNodes();

void setLabel(const std::string &label);

void setNodeColor(const std::string &color);

void setBackgroundColor(const std::string &backgroundColor);

void setSize(float size);

void setType(const std::string &type);

void setDirection(const std::string &direction);

#endif //NODE_H
