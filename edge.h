#ifndef EDGE_H
#define EDGE_H

typedef struct Edge Edge;
struct Edge {
    char *dest;
    char *source;
    char *id;
    float pos_x;
    float pos_y;
    char *label;
    char *color;
    char *path;
};

void init_current_edge();

void create_edge_pos(char *source, char *dest, char *label, float pos_x, float pos_y);

void create_edge(char *source, char *dest, char *label);

#endif