#ifndef EDGE_H
#define EDGE_H

typedef struct Edge Edge;
struct Edge {
    char *id;
    char *source;
    char *dest;
    float xPos;
    float yPos;
    char *label;
    char *color;
    char *path;
    Edge *next;
};

typedef struct EdgesList EdgesList;
struct EdgesList {
    Edge *firstEdge;
};

void declareCurrentEdge();

void declareEdgesList();

void initCurrentEdge();

Edge *copyCurrentEdge();

void printEdge(Edge *edge);

void printEdgesList();

void addEdge(Edge *newEdge);

void removeEdge(char *source, char *dest);

void renameEdgeNode(char *previousNodeId, char *newNodeId);

void removeEdgesContainingNode(const char *nodeId);

void createEdgePos(char *source, char *dest, char *label, float xPos, float yPos);

void createEdge(char *source, char *dest, char *label);

void setEdgeColor(char *color);

void setPath(char *path);

#endif