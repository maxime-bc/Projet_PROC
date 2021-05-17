#include <iostream>
#include <string>
#include <list>

#include "node.h"

std::list<Node> NODES;
Node CURRENT_NODE = {};

void createNode(char *id, float xPos, float yPos) {
    std::string str(id);

    if (nodeExists(id)) {
        std::cout << "ERROR : Node " << id << " already exists." << std::endl;
        return;
    }

    CURRENT_NODE.id = id;
    CURRENT_NODE.xPos = xPos;
    CURRENT_NODE.yPos = yPos;

    Node newNode = CURRENT_NODE;
    NODES.push_back(newNode);

    CURRENT_NODE = {};

    printNodes(NODES);
}

bool nodeExists(const std::string &nodeId) {
    bool exists = false;

    for (const auto &node : NODES) {
        if (node.id == nodeId) {
            exists = true;
            break;
        }
    }
    return exists;
}

void printNodes(const std::list<Node> &nodes) {
    for (const auto &node : nodes) {
        std::cout << "node " << node.id << " {xPos=" << node.xPos << ", yPos=" << node.yPos << ", label=" << node.label
                  << ", color=" << node.color << ", backgroundColor=" << node.backgroundColor << ", size=" << node.size
                  << ", type=" << node.type << ", direction=" << node.direction << "}\n";
    }
}

void setLabel(char *label) {
    std::string str(label);
    CURRENT_NODE.label = label;
}

void setNodeColor(char *color) {
    std::string str(color);
    CURRENT_NODE.color = color;
}

void setBgColor(char *backgroundColor) {
    std::string str(backgroundColor);
    CURRENT_NODE.backgroundColor = backgroundColor;
}

void setSize(float size) {
    CURRENT_NODE.size = size;
}

void setType(char *type) {
    std::string str(type);
    CURRENT_NODE.type = type;
}

void setDirection(char *direction) {
    std::string str(direction);
    CURRENT_NODE.direction = direction;
}