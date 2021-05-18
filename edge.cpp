#include <iostream>
#include <string>
#include <list>

#include "edge.h"
#include "node.h"

std::list<Edge> EDGES;
Edge CURRENT_EDGE = {};


void createEdgeWithPosition(const std::string &source, const std::string &dest, const std::string &label, float xPos,
                            float yPos) {

    if (!nodeExists(source)) {
        std::cout << "ERROR : Node " << source << " doesn't exists." << std::endl;
        return;
    }

    if (!nodeExists(dest)) {
        std::cout << "ERROR : Node " << dest << " doesn't exists." << std::endl;
        return;
    }

    CURRENT_EDGE.source = source;
    CURRENT_EDGE.dest = dest;
    CURRENT_EDGE.label = label;
    CURRENT_EDGE.xPos = xPos;
    CURRENT_EDGE.yPos = yPos;

    Edge newEdge = CURRENT_EDGE;
    EDGES.push_back(newEdge);

    CURRENT_EDGE = {};
}


void createEdge(const std::string &source, const std::string &dest, const std::string &label) {
    float xPos = 0;
    float yPos = 0;
    createEdgeWithPosition(source, dest, label, xPos, yPos);
}

void removeEdge(const std::string &source, const std::string &dest) {
    bool removed = false;

    for (auto edge = EDGES.begin(); edge != EDGES.end();) {
        if (edge->dest == dest && edge->source == source) {
            EDGES.erase(edge);
            removed = true;
            break;
        } else
            edge++;
    }

    if (!removed) {
        std::cout << "ERROR : Edge " << source << " - " << dest << " wasn't found." << std::endl;
    }
}

void removeEdgesContainingNode(const std::string &nodeId) {
    for (auto edge = EDGES.begin(); edge != EDGES.end();) {
        if (edge->source == nodeId || edge->dest == nodeId) {
            edge = EDGES.erase(edge);
        } else {
            edge++;
        }
    }
}

void renameEdgeNode(const std::string &currentNodeId, const std::string &newNodeId) {
    for (auto &edge : EDGES) {
        if (edge.source == currentNodeId) {
            edge.source = newNodeId;
        }

        if (edge.dest == currentNodeId) {
            edge.dest = newNodeId;
        }
    }
}

void printEdges() {
    for (const auto &edge : EDGES) {
        std::cout << "edge " << edge.source << " - " << edge.dest << " {xPos=" << edge.xPos << ", yPos=" << edge.yPos
                  << ", label=" << edge.label << ", color=" << edge.color << ", path=" << edge.path << "}" << std::endl;
    }
}

void setEdgeColor(const std::string &color) {
    CURRENT_EDGE.color = color;
}

void setPath(const std::string &path) {
    CURRENT_EDGE.path = path;
}