#include <iostream>
#include <string>
#include <list>

#include "edge.h"
#include "node.h"

std::list<Edge> EDGES;
Edge CURRENT_EDGE = {};


void createEdgeWithPositions(char *source, char *dest, char *label, float xPos, float yPos) {

    if (!nodeExists(source)) {
        std::cout << "ERROR : Node " << source << " doesn't exists." << std::endl;
    } else if (!nodeExists(dest)) {
        std::cout << "ERROR : Node " << dest << " doesn't exists." << std::endl;
    } else {
        CURRENT_EDGE.source = source;
        CURRENT_EDGE.dest = dest;
        CURRENT_EDGE.label = label;
        CURRENT_EDGE.xPos = xPos;
        CURRENT_EDGE.yPos = yPos;

        Edge newEdge = CURRENT_EDGE;
        EDGES.push_back(newEdge);

        CURRENT_EDGE = {};
    }
}


void createEdge(char *source, char *dest, char *label) {
    float xPos = 0;
    float yPos = 0;
    createEdgeWithPositions(source, dest, label, xPos, yPos);
}

void removeEdge(char *source, char *dest) {
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
        } else
            edge++;
    }
}

void printEdges() {
    for (const auto &edge : EDGES) {
        std::cout << "edge " << edge.source << " - " << edge.dest << " {xPos=" << edge.xPos << ", yPos=" << edge.yPos
                  << ", label=" << edge.label << ", color=" << edge.color << ", path=" << edge.path << "}" << std::endl;
    }
}

void setEdgeColor(char *color) {
    CURRENT_EDGE.color = color;
}

void setPath(char *path) {
    CURRENT_EDGE.path = path;
}