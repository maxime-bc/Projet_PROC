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

        printEdges(EDGES);
    }
}


void createEdge(char *source, char *dest, char *label) {
    float xPos = 0;
    float yPos = 0;
    createEdgeWithPositions(source, dest, label, xPos, yPos);
}

void printEdges(const std::list<Edge> &edges) {
    for (const auto &edge : edges) {
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