#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "edge.h"
#include "node.h"

Edge *CURRENT_EDGE = NULL;
EdgesList *EDGES_LIST = NULL;

void declareCurrentEdge() {
    if (CURRENT_EDGE == NULL) {
        CURRENT_EDGE = malloc(sizeof(*CURRENT_EDGE));
        initCurrentEdge();
    }
}

void declareEdgesList() {
    if (EDGES_LIST == NULL) {
        EDGES_LIST = malloc(sizeof(*EDGES_LIST));
    }
}

void initCurrentEdge() {
    CURRENT_EDGE->id = "";
    CURRENT_EDGE->source = "";
    CURRENT_EDGE->dest = "";
    CURRENT_EDGE->xPos = 0;
    CURRENT_EDGE->yPos = 0;
    CURRENT_EDGE->label = "";
    CURRENT_EDGE->color = "";
    CURRENT_EDGE->path = "";
}

Edge *copyCurrentEdge() {
    Edge *edgeCopy = malloc(sizeof(*edgeCopy));
    edgeCopy->id = CURRENT_EDGE->id;
    edgeCopy->source = CURRENT_EDGE->source;
    edgeCopy->dest = CURRENT_EDGE->dest;
    edgeCopy->xPos = CURRENT_EDGE->xPos;
    edgeCopy->yPos = CURRENT_EDGE->yPos;
    edgeCopy->label = CURRENT_EDGE->label;
    edgeCopy->color = CURRENT_EDGE->color;
    edgeCopy->path = CURRENT_EDGE->path;
    return edgeCopy;
}

void printEdge(Edge *edge) {
    printf("edge %s - %s {xPos=%f, yPos=%f, label=%s, color=%s, path=%s}\n",
           edge->source, edge->dest, edge->xPos, edge->yPos, edge->label, edge->color, edge->path);
}

void printEdgesList() {
    declareEdgesList();
    Edge *edge = EDGES_LIST->firstEdge;
    while (edge != NULL) {
        printEdge(edge);
        edge = edge->next;
    }
}

void addEdge(Edge *newEdge) {
    newEdge->next = EDGES_LIST->firstEdge;
    EDGES_LIST->firstEdge = newEdge;
}

void renameEdgeNode(char *previousNodeId, char *newNodeId) {
    Edge *currentEdge = EDGES_LIST->firstEdge;

    while (currentEdge != NULL) {
        if (strcmp(currentEdge->source, previousNodeId) == 0) {
            currentEdge->source = newNodeId;
        } else if (strcmp(currentEdge->dest, previousNodeId) == 0) {
            currentEdge->dest = newNodeId;
        }
        currentEdge = currentEdge->next;
    }
}

void removeEdge(char *source, char *dest) {
    int exists = 0;
    Edge *previousEdge, *currentEdge;

    declareEdgesList();
    currentEdge = EDGES_LIST->firstEdge;
    previousEdge = currentEdge;

    while (currentEdge != NULL) {

        if (strcmp(currentEdge->source, source) == 0 && strcmp(currentEdge->dest, dest) == 0) {
            exists = 1;
            if (previousEdge == currentEdge) {
                EDGES_LIST->firstEdge = currentEdge->next;
                free(currentEdge);
            } else {
                previousEdge->next = currentEdge->next;
                free(currentEdge);
            }
            break;
        }
        previousEdge = currentEdge;
        currentEdge = currentEdge->next;
    }

    if (!exists) {
        printf("ERROR : Edge %s - %s doesn't exists.\n", source, dest);
    }
}

void removeEdgesContainingNode(const char *nodeId) {
    Edge *previousEdge, *currentEdge;

    declareEdgesList();
    currentEdge = EDGES_LIST->firstEdge;
    previousEdge = currentEdge;

    while (currentEdge != NULL) {

        if (strcmp(currentEdge->source, nodeId) == 0 || strcmp(currentEdge->dest, nodeId) == 0) {

            if (previousEdge == currentEdge) {  // first element
                EDGES_LIST->firstEdge = currentEdge->next;
                free(currentEdge);
                currentEdge = EDGES_LIST->firstEdge;
                previousEdge = currentEdge;
            } else {
                previousEdge->next = currentEdge->next;
                free(currentEdge);
                currentEdge = previousEdge->next;
            }
        } else {
            currentEdge = currentEdge->next;
        }
    }
}


void createEdgePos(char *source, char *dest, char *label, float xPos, float yPos) {
    declareCurrentEdge();
    declareEdgesList();

    declareNodesList();

    if (!nodeExists(source)) {
        printf("ERROR : Node %s doesn't exists.\n", source);
    } else if (!nodeExists(dest)) {
        printf("ERROR : Node %s doesn't exists.\n", dest);
    } else {
        // TODO: id
        //char prefix[30] = "";
        //CURRENT_EDGE->id = snprintf(prefix,"%s%s", source, dest);
        // source + dest + label
        CURRENT_EDGE->source = source;
        CURRENT_EDGE->dest = dest;
        CURRENT_EDGE->label = label;
        CURRENT_EDGE->xPos = xPos;
        CURRENT_EDGE->yPos = yPos;

        addEdge(copyCurrentEdge());
        initCurrentEdge();
    }
}

void createEdge(char *source, char *dest, char *label) {
    float xPos = 0, yPos = 0;
    // TODO: calcul des pos
    createEdgePos(source, dest, label, xPos, yPos);
}


void setEdgeColor(char *color) {
    declareCurrentEdge();
    CURRENT_EDGE->color = color;
}

void setPath(char *path) {
    declareCurrentEdge();
    CURRENT_EDGE->path = path;
}