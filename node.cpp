#include <iostream>
#include <string>
#include <list>
#include <utility>

#include "node.h"
#include "edge.h"

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
}

void removeNode(char *id) {
    if (!nodeExists(id)) {
        std::cout << "ERROR : Node " << id << " doesn't exists." << std::endl;
    }

    removeEdgesContainingNode(id);

    for (auto node = NODES.begin(); node != NODES.end();) {
        if (node->id == id) {
            NODES.erase(node);
            break;
        } else
            node++;
    }
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

void printNodes() {
    for (const auto &node : NODES) {
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