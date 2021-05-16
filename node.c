#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "node.h"
#include "edge.h"

/** Global variables */

Node *CURRENT_NODE = NULL;
NodesList *NODES_LIST = NULL;
IDList *IDS_LIST = NULL;
const char *INITIAL = "initial";
const char *FINAL = "final";

/** Functions to handle IDs list for move **/

void declareIdsList() {
    if (IDS_LIST == NULL) {
        IDS_LIST = malloc(sizeof(*IDS_LIST));
        IDS_LIST->firstId = NULL;
    }
}

void addId(char *id) {
    declareIdsList();

    Id *newId = malloc(sizeof(*newId));
    newId->id = id;
    newId->next = IDS_LIST->firstId;
    IDS_LIST->firstId = newId;
}

void printIdsList() {
    Id *currentId = IDS_LIST->firstId;

    while (currentId != NULL) {
        printf("ID %s\n", currentId->id);
        currentId = currentId->next;
    }
}

void moveMultipleNodesById(float xOffset, float yOffset) {
    Id *currentId = IDS_LIST->firstId;
    while (currentId != NULL) {
        moveNode(currentId->id, xOffset, yOffset);

        IDS_LIST->firstId = currentId->next;
        free(currentId);
        currentId = IDS_LIST->firstId;
    }
    IDS_LIST->firstId = NULL;
}

/** Functions to handle nodes **/

void declareCurrentNode() {
    if (CURRENT_NODE == NULL) {
        CURRENT_NODE = malloc(sizeof(*CURRENT_NODE));
        initCurrentNode();
    }
}

void declareNodesList() {
    if (NODES_LIST == NULL) {
        NODES_LIST = malloc(sizeof(*NODES_LIST));
    }
}

void initCurrentNode() {
    CURRENT_NODE->id = "";
    CURRENT_NODE->xPos = 0;
    CURRENT_NODE->yPos = 0;
    CURRENT_NODE->label = "";
    CURRENT_NODE->color = "";
    CURRENT_NODE->bgColor = "";
    CURRENT_NODE->size = 30;
    CURRENT_NODE->type = "";
    CURRENT_NODE->direction = "";
    CURRENT_NODE->next = NULL;
}

Node *copyCurrentNode() {
    Node *nodeCopy = malloc(sizeof(*nodeCopy));
    nodeCopy->id = CURRENT_NODE->id;
    nodeCopy->xPos = CURRENT_NODE->xPos;
    nodeCopy->yPos = CURRENT_NODE->yPos;
    nodeCopy->label = CURRENT_NODE->label;
    nodeCopy->color = CURRENT_NODE->color;
    nodeCopy->bgColor = CURRENT_NODE->bgColor;
    nodeCopy->size = CURRENT_NODE->size;
    nodeCopy->type = CURRENT_NODE->type;
    nodeCopy->direction = CURRENT_NODE->direction;
    nodeCopy->next = CURRENT_NODE->next;
    return nodeCopy;
}

void printNode(Node *node) {
    printf("node %s {xPos=%f, yPos=%f, label=%s, color=%s, bgcolor=%s, size=%f, type=%s, direction=%s}\n",
           node->id, node->xPos, node->yPos, node->label, node->color, node->bgColor, node->size, node->type,
           node->direction);
}

void printNodesList() {
    declareNodesList();
    Node *node = NODES_LIST->firstNode;
    while (node != NULL) {
        printNode(node);
        node = node->next;
    }
}

void addNode(Node *node) {
    node->next = NODES_LIST->firstNode;
    NODES_LIST->firstNode = node;
}

void removeNode(const char *nodeId) {
    int exists = 0;
    Node *previousNode, *currentNode;

    declareNodesList();

    removeEdgesContainingNode(nodeId);
    currentNode = NODES_LIST->firstNode;
    previousNode = currentNode;

    while (currentNode != NULL) {

        if (strcmp(currentNode->id, nodeId) == 0) {
            exists = 1;
            if (previousNode == currentNode) {
                NODES_LIST->firstNode = currentNode->next;
                free(currentNode);
            } else {
                previousNode->next = currentNode->next;
                free(currentNode);
            }
            break;
        }
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if (!exists) {
        printf("ERROR : Node %s doesn't exists.\n", nodeId);
    }
}

void createNode(char *id, float xPos, float yPos) {
    declareCurrentNode();
    declareNodesList();

    if (nodeExists(id)) {
        printf("ERROR : Node %s already exists.\n", id);
    } else {
        CURRENT_NODE->id = id;
        CURRENT_NODE->xPos = xPos;
        CURRENT_NODE->yPos = yPos;

        if (*CURRENT_NODE->label == '\0') {
            CURRENT_NODE->label = id;
        }

        if (*CURRENT_NODE->direction == '\0') { // TODO : choose best direction
            if (strcmp(CURRENT_NODE->type, INITIAL) == 0) {
                CURRENT_NODE->direction = "west";
            } else if (strcmp(CURRENT_NODE->type, FINAL) == 0) {
                CURRENT_NODE->direction = "east";
            }
        }
        addNode(copyCurrentNode());
        initCurrentNode();
    }
}

int nodeExists(char *nodeId) {
    int exists = 0;
    Node *currNode = NODES_LIST->firstNode;

    while (currNode != NULL) {
        if (strcmp(currNode->id, nodeId) == 0) {
            exists = 1;
            break;
        }
        currNode = currNode->next;
    }
    return exists;
}

void moveAllNodes(float xOffset, float yOffset) {
    declareNodesList();

    Node *currentNode = NODES_LIST->firstNode;

    while (currentNode != NULL) {
        currentNode->xPos += xOffset;
        currentNode->yPos += yOffset;
        currentNode = currentNode->next;
    }
}

void moveNode(char *nodeId, float xOffset, float yOffset) {
    declareNodesList();

    if (!nodeExists(nodeId)) {
        printf("ERROR : Node %s doesn't exists.\n", nodeId);
        return;
    }

    Node *currentNode = NODES_LIST->firstNode;
    while (currentNode != NULL) {
        if (strcmp(currentNode->id, nodeId) == 0) {
            currentNode->xPos += xOffset;
            currentNode->yPos += yOffset;
        }
        currentNode = currentNode->next;
    }
}

void renameNode(char *currentId, char *newId) { // TODO: rename all edges
    declareNodesList();

    if (!nodeExists(currentId)) {
        printf("ERROR : Node %s doesn't exists.\n", currentId);
        return;
    }

    if (nodeExists(newId)) {
        printf("ERROR : Node %s already exists.\n", newId);
        return;
    }

    Node *currentNode = NODES_LIST->firstNode;
    while (currentNode != NULL) {
        if (strcmp(currentNode->id, currentId) == 0) {
            currentNode->id = newId;
        }
        currentNode = currentNode->next;
    }
}

void setLabel(char *label) {
    declareCurrentNode();
    CURRENT_NODE->label = label;
}

void setNodeColor(char *color) {
    declareCurrentNode();
    CURRENT_NODE->color = color;
}

void setBgColor(char *bgColor) {
    declareCurrentNode();
    CURRENT_NODE->bgColor = bgColor;
}

void setSize(float size) {
    declareCurrentNode();
    CURRENT_NODE->size = size;
}

void setType(char *type) {
    declareCurrentNode();
    CURRENT_NODE->type = type;
}

void setDirection(char *direction) {
    declareCurrentNode();
    CURRENT_NODE->direction = direction;
}