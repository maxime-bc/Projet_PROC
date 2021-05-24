#include <iostream>
#include <string>
#include <list>

#include "node.h"
#include "edge.h"

std::list<Node> NODES;
Node CURRENT_NODE = {};
std::list<std::string> IDS_LIST;

void createNode(const std::string &nodeId, float xPos, float yPos) {
    if (getNodeIndex(nodeId) != -1) {
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

void removeNode(const std::string &nodeId) {
    int nodePos = getNodeIndex(nodeId);

    if (nodePos == -1) {
        std::cout << "ERROR : Node " << nodeId << " doesn't exists." << std::endl;
        return;
    }

    removeEdgesContainingNode(nodeId);

    auto nodesIterator = NODES.begin();
    std::advance(nodesIterator, nodePos);
    NODES.erase(nodesIterator);
}

int getNodeIndex(const std::string &nodeId) {
    int index = 0;
    for (const Node &node : NODES) {
        if (node.id == nodeId) {
            return index;
        }
        index += 1;
    }
    return -1;
}

void renameNode(const std::string &currentNodeId, const std::string &newNodeId) {
    int currentNodePos = getNodeIndex(currentNodeId);

    if (currentNodePos == -1) {
        std::cout << "ERROR : Node " << currentNodeId << " doesn't exists." << std::endl;
        return;
    }

    if (getNodeIndex(newNodeId) != -1) {
        std::cout << "ERROR : Node " << newNodeId << " already exists." << std::endl;
        return;
    }

    renameEdgeNode(currentNodeId, newNodeId);

    auto nodesIterator = NODES.begin();
    std::advance(nodesIterator, currentNodePos);

    nodesIterator->id = newNodeId;
    if (nodesIterator->label == currentNodeId) { // change default label by new id value.
        nodesIterator->label = newNodeId;
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

    int nodePos = getNodeIndex(nodeId);
    if (nodePos == -1) {
        std::cout << "ERROR : Node " << nodeId << " doesn't exists." << std::endl;
        return;
    }

    auto nodesIterator = NODES.begin();
    std::advance(nodesIterator, nodePos);
    nodesIterator->xPos += xPos;
    nodesIterator->yPos += yPos;
}

void editNode(const std::string &nodeId) {

    int nodePos = getNodeIndex(nodeId);
    if (nodePos == -1) {
        std::cout << "ERROR : Node " << nodeId << " doesn't exists." << std::endl;
        return;
    }

    auto nodesIterator = NODES.begin();
    std::advance(nodesIterator, nodePos);

    if (!CURRENT_NODE.label.empty()) {
        nodesIterator->label = CURRENT_NODE.label;
    }

    if (!CURRENT_NODE.color.empty()) {
        nodesIterator->color = CURRENT_NODE.color;
    }

    if (!CURRENT_NODE.backgroundColor.empty()) {
        nodesIterator->backgroundColor = CURRENT_NODE.backgroundColor;
    }

    if (!CURRENT_NODE.initial.empty()) {
        nodesIterator->initial = CURRENT_NODE.initial;
    }

    if (!CURRENT_NODE.final.empty()) {
        nodesIterator->final = CURRENT_NODE.final;
    }

    if (CURRENT_NODE.size >= 0) {
        nodesIterator->size = CURRENT_NODE.size;
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

void setNodeLabel(const std::string &label) {
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
            CURRENT_NODE.final = direction;
        }
    }
}