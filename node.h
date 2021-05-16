#ifndef NODE_H
#define NODE_H

typedef struct Node Node;
struct Node {
    char *id;
    float xPos;
    float yPos;
    char *label;
    char *color;
    char *bgColor;
    float size;
    char *type;
    char *direction;
    Node *next;
};

typedef struct NodesList NodesList;
struct NodesList {
    Node *firstNode;
};


typedef struct Id Id;
struct Id {
    char *id;
    Id *next;
};

typedef struct IDList IDList;
struct IDList {
    Id *firstId;
};

void declareIdsList();

void addId(char *id);

void moveMultipleNodesById(float xOffset, float yOffset);

void printIdsList();

void declareCurrentNode();

void declareNodesList();

void initCurrentNode(void);

Node *copyCurrentNode(void);

void printNode(Node *node);

void printNodesList();

void addNode(Node *node);

void removeNode(const char *nodeId);

void createNode(char *id, float xPos, float yPos);

int nodeExists(char *nodeId);

void moveAllNodes(float xOffset, float yOffset);

void moveNode(char *nodeId, float xOffset, float yOffset);

void renameNode(char *currentId, char *newId);

void setLabel(char *label);

void setNodeColor(char *color);

void setType(char *type);

void setBgColor(char *bgColor);

void setSize(float size);

void setDirection(char *direction);

#endif