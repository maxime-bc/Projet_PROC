#include <iostream>
#include <string>
#include <list>

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

    if (CURRENT_NODE.color.empty()) {
        CURRENT_NODE.color = "black";
    }

    if (CURRENT_NODE.backgroundColor.empty()) {
        CURRENT_NODE.backgroundColor = "none";
    }

    if (CURRENT_NODE.size < 0) {
        CURRENT_NODE.size = 30;
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
                  << ", initial=" << node.initial << ", final=" << node.final << "}" << std::endl;
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

void editNode(const std::string &nodeId) {

    if (!nodeExists(nodeId)) {
        std::cout << "ERROR : Node " << nodeId << " doesn't exists." << std::endl;
        return;
    }

    for (auto node = NODES.begin(); node != NODES.end();) {
        if (node->id == nodeId) {
            if (!CURRENT_NODE.label.empty()) {
                node->label = CURRENT_NODE.label;
            }

            if (!CURRENT_NODE.color.empty()) {
                node->color = CURRENT_NODE.color;
            }

            if (!CURRENT_NODE.backgroundColor.empty()) {
                node->backgroundColor = CURRENT_NODE.backgroundColor;
            }
            // TODO: fix update final and initial
            if (!CURRENT_NODE.initial.empty()) {
                node->initial = CURRENT_NODE.initial;
            }

            if (!CURRENT_NODE.final.empty()) {
                node->final = CURRENT_NODE.final;
            }

            if (CURRENT_NODE.size >= 0) {
                node->size = CURRENT_NODE.size;
            }
            break;
        } else
            node++;
    }

    CURRENT_NODE = {};
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

void setType(const std::string &type, const std::string &direction) {
    if (type == "initial") {
        if (direction.empty()) {
            CURRENT_NODE.initial = "west";
        } else {
            CURRENT_NODE.initial = direction;
        }
    } else if (type == "final") {
        if (direction.empty()) {
            CURRENT_NODE.final = "east";
        } else {
            CURRENT_NODE.initial = direction;
        }
    }
}