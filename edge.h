#ifndef EDGE_H
#define EDGE_H

typedef struct Edge Edge;
struct Edge {
    char *id;
    char *source;
    char *dest;
    float pos_x;
    float pos_y;
    char *label;
    char *color;
    char *path;
    Edge *next;
};

typedef struct EdgesList EdgesList;
struct EdgesList {
    Edge *first_edge;
};

void declare_current_edge();

void declare_edges_list();

void init_current_edge();

Edge *copy_current_edge();

void print_edge(Edge *edge);

void print_edges_list();

void add_edge(Edge *new_edge);

void remove_edge(char *source, char *dest);

void create_edge_pos(char *source, char *dest, char *label, float pos_x, float pos_y);

void create_edge(char *source, char *dest, char *label);

void set_edge_color(char *color);

void set_path(char *path);

#endif