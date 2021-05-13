#ifndef STRUCT_H
#define STRUCT_H

typedef struct Node Node;
struct Node {
    char* id;
    float pos_x;
    float pos_y;
    char* label;
    char* color;
    char* bgcolor;
    float size;
    char* initial;
    char* fnl;
};

void create_node(char* id, float pos_x, float pos_y);

void set_label(char* label);

#endif