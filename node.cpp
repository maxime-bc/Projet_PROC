#include <iostream>
#include <string>
#include <list>
#include <utility>

#include "node.h"

std::list<Node> NODES;
Node CURRENT_NODE = {};

void createNode(char *id, float xPos, float yPos) {

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
                  << ", type=" << node.type << ", direction=" << node.direction << "}" << std::endl;
    }
}

void setLabel(char *label) {
    CURRENT_NODE.label = label;
}

void setNodeColor(char *color) {
    CURRENT_NODE.color = color;
}

void setBgColor(char *backgroundColor) {
    CURRENT_NODE.backgroundColor = backgroundColor;
}

void setSize(float size) {
    CURRENT_NODE.size = size;
}

void setType(std::string type) {
    CURRENT_NODE.type = std::move(type);
}

void setDirection(std::string direction) {
    CURRENT_NODE.direction = std::move(direction);
}