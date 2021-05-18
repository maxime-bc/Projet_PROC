#include <iostream>
#include <string>
#include <list>
#include <utility>

#include "node.h"
#include "edge.h"

std::list<Node> NODES;
Node CURRENT_NODE = {};
std::list<std::string> IDS_LIST;

void createNode(const std::string &nodeId, float xPos, float yPos) {
    if (nodeExists(nodeId)) {
        std::cout << "ERROR : Node " << nodeId << " already exists." << std::endl;
        return;
    }

    CURRENT_NODE.id = nodeId;
    CURRENT_NODE.xPos = xPos;
    CURRENT_NODE.yPos = yPos;

    // Set default attributes
    if (CURRENT_NODE.label.empty()) {
        CURRENT_NODE.label = nodeId;
    }

    if (CURRENT_NODE.direction.empty()) {
        if (CURRENT_NODE.type == "initial") {
            CURRENT_NODE.direction = "west";
        } else if (CURRENT_NODE.type == "final") {
            CURRENT_NODE.direction = "east";
        }
    }

    Node newNode = CURRENT_NODE;
    NODES.push_back(newNode);

    CURRENT_NODE = {};
}

void removeNode(const std::string &id) {
    if (!nodeExists(id)) {
        std::cout << "ERROR : Node " << id << " doesn't exists." << std::endl;
        return;
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

    for (const Node &node : NODES) {
        if (node.id == nodeId) {
            exists = true;
            break;
        }
    }
    return exists;
}

void renameNode(const std::string &currentNodeId, const std::string &newNodeId) {

    if (!nodeExists(currentNodeId)) {
        std::cout << "ERROR : Node " << currentNodeId << " doesn't exists." << std::endl;
        return;
    }

    if (nodeExists(newNodeId)) {
        std::cout << "ERROR : Node " << newNodeId << " already exists." << std::endl;
        return;
    }

    renameEdgeNode(currentNodeId, newNodeId);

    for (auto &node : NODES) {
        if (node.id == currentNodeId) {
            node.id = newNodeId;

            if (node.label == currentNodeId) { // change default label by new id value.
                node.label = newNodeId;
            }
            break;
        }
    }
}

void printNodes() {
    for (const Node &node : NODES) {
        std::cout << "node " << node.id << " {xPos=" << node.xPos << ", yPos=" << node.yPos << ", label=" << node.label
                  << ", color=" << node.color << ", backgroundColor=" << node.backgroundColor << ", size=" << node.size
                  << ", type=" << node.type << ", direction=" << node.direction << "}" << std::endl;
    }
}

void moveAllNodes(float xPos, float yPos) {
    for (auto &node : NODES) {
        node.xPos += xPos;
        node.yPos += yPos;
    }
}

void moveNode(const std::string &nodeId, float xPos, float yPos) {
    if (!nodeExists(nodeId)) {
        std::cout << "ERROR : Node " << nodeId << " doesn't exists." << std::endl;
        return;
    }

    for (auto &node : NODES) {
        if (node.id == nodeId) {
            node.xPos += xPos;
            node.yPos += yPos;
            break;
        }
    }
}

void moveMultipleNodesById(float xPos, float yPos) {
    for (auto &id: IDS_LIST) {
        moveNode(id, xPos, yPos);
    }
    IDS_LIST.clear();
}

void addId(const std::string &id) {
    IDS_LIST.emplace_back(id);
}

void setLabel(const std::string &label) {
    CURRENT_NODE.label = label;
}

void setNodeColor(const std::string &color) {
    CURRENT_NODE.color = color;
}

void setBackgroundColor(const std::string &backgroundColor) {
    CURRENT_NODE.backgroundColor = backgroundColor;
}

void setSize(float size) {
    CURRENT_NODE.size = size;
}

void setType(const std::string &type) {
    CURRENT_NODE.type = type;
}

void setDirection(const std::string &direction) {
    CURRENT_NODE.direction = direction;
}