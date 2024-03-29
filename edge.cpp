#include <iostream>
#include <string>
#include <list>

#include "edge.h"
#include "node.h"

std::list<Edge> EDGES_LIST;
Edge CURRENT_EDGE = {};


void createEdge(const std::string &source, const std::string &dest, const std::string &label, float xPos,
                float yPos) {

    if (getNodeIndex(source) == -1) {
        std::cerr << "ERROR : Node " << source << " doesn't exists." << std::endl;
        CURRENT_EDGE = {};
        return;
    }

    if (getNodeIndex(dest) == -1) {
        std::cerr << "ERROR : Node " << dest << " doesn't exists." << std::endl;
        CURRENT_EDGE = {};
        return;
    }

    if (getEdgeIndex(source, dest) != -1) {
        std::cerr << "ERROR : Edge " << source << " - " << dest << " already exists." << std::endl;
        CURRENT_EDGE = {};
        return;
    }

    CURRENT_EDGE.source = source;
    CURRENT_EDGE.dest = dest;
    CURRENT_EDGE.label = label;
    CURRENT_EDGE.xPos = xPos;
    CURRENT_EDGE.yPos = yPos;

    Edge newEdge = CURRENT_EDGE;
    EDGES_LIST.push_back(newEdge);

    CURRENT_EDGE = {};
}

void removeEdge(const std::string &source, const std::string &dest) {

    int edgePos = getEdgeIndex(source, dest);
    if (edgePos == -1) {
        std::cerr << "ERROR : Edge " << source << " - " << dest << " doesn't exists." << std::endl;
        return;
    }

    auto edgesIterator = EDGES_LIST.begin();
    std::advance(edgesIterator, getEdgeIndex(source, dest));
    EDGES_LIST.erase(edgesIterator);
}

void removeEdgesContainingNode(const std::string &nodeId) {
    for (auto edge = EDGES_LIST.begin(); edge != EDGES_LIST.end();) {
        if (edge->source == nodeId || edge->dest == nodeId) {
            edge = EDGES_LIST.erase(edge);
        } else {
            edge++;
        }
    }
}

void renameEdgeNode(const std::string &currentNodeId, const std::string &newNodeId) {
    for (auto &edge : EDGES_LIST) {
        if (edge.source == currentNodeId) {
            edge.source = newNodeId;
        }

        if (edge.dest == currentNodeId) {
            edge.dest = newNodeId;
        }
    }
}

int getEdgeIndex(const std::string &source, const std::string &dest) {
    int index = 0;
    for (const Edge &edge : EDGES_LIST) {
        if (edge.source == source && edge.dest == dest) {
            return index;
        }
        index += 1;
    }
    return -1;
}


void editEdge(const std::string &source, const std::string &dest) {

    int edgePos = getEdgeIndex(source, dest);
    if (edgePos == -1) {
        std::cerr << "ERROR : Edge " << source << " - " << dest << " doesn't exists." << std::endl;
        CURRENT_EDGE = {};
        return;
    }

    auto edgesIterator = EDGES_LIST.begin();
    std::advance(edgesIterator, edgePos);

    if (!CURRENT_EDGE.color.empty()) {
        edgesIterator->color = CURRENT_EDGE.color;
    }

    if (!CURRENT_EDGE.path.empty()) {
        edgesIterator->path = CURRENT_EDGE.path;
    }

    if (!CURRENT_EDGE.label.empty()) {
        edgesIterator->label = CURRENT_EDGE.label;
    }

    if (CURRENT_EDGE.xPos != -1) {
        edgesIterator->xPos = CURRENT_EDGE.xPos;
    }

    if (CURRENT_EDGE.yPos != -1) {
        edgesIterator->yPos = CURRENT_EDGE.yPos;
    }

    CURRENT_EDGE = {};
}

void printEdges() {
    for (const auto &edge : EDGES_LIST) {
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

void setEdgeLabel(const std::string &label) {
    CURRENT_EDGE.label = label;
    CURRENT_EDGE.xPos = 0;
    CURRENT_EDGE.yPos = 0;
}

void setEdgeLabelWithPos(const std::string &label, float x, float y) {
    CURRENT_EDGE.label = label;
    CURRENT_EDGE.xPos = x;
    CURRENT_EDGE.yPos = y;
}