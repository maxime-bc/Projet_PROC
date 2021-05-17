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

void createNode(char *id, float xPos, float yPos);

void removeNode(char *id);

bool nodeExists(const std::string& nodeId);

void printNodes();

void setLabel(char *label);

void setNodeColor(char *color);

void setBgColor(char *backgroundColor);

void setSize(float size);

void setType(std::string type);

void setDirection(std::string direction);

#endif //NODE_H
