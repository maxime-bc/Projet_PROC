#include <stdlib.h>
#include <stdio.h>
#include "edge.h"

Edge *current_edge;
EdgesList *edges_list;

void declare_current_edge() {
    if (!current_edge) {
        current_edge = malloc(sizeof(*current_edge));
        init_current_edge();
    }
}

void declare_edges_list() {
    if (!edges_list) {
        edges_list = malloc(sizeof(*edges_list));
    }
}

void init_current_edge() {
    current_edge->id = "";
    current_edge->source = "";
    current_edge->dest = "";
    current_edge->pos_x = 0;
    current_edge->pos_y = 0;
    current_edge->label = "";
    current_edge->color = "";
    current_edge->path = "";
}

Edge *copy_current_edge() {
    Edge *edge_copy = malloc(sizeof(*edge_copy));
    edge_copy->id = current_edge->id;
    edge_copy->source = current_edge->source;
    edge_copy->dest = current_edge->dest;
    edge_copy->pos_x = current_edge->pos_x;
    edge_copy->pos_y = current_edge->pos_y;
    edge_copy->label = current_edge->label;
    edge_copy->color = current_edge->color;
    edge_copy->path = current_edge->path;
    return edge_copy;
}

void print_edge(Edge *edge) {
    printf("ID = %s, SOURCE = %s, DEST = %s\n"
           "X = %f, Y = %f, LABEL = %s, COLOR = %s, PATH = %s\n\n",
           edge->id, edge->source, edge->dest, edge->pos_x, edge->pos_y,
           edge->label, edge->color, edge->path);

}

void print_edges_list() {
    declare_edges_list();
    Edge *edge = edges_list->first_edge;
    while (edge != NULL) {
        print_edge(edge);
        edge = edge->next;
    }
}

void add_edge(Edge *new_edge) {
    new_edge->next = edges_list->first_edge;
    edges_list->first_edge = new_edge;
}

void create_edge_pos(char *source, char *dest, char *label, float pos_x, float pos_y) {
    declare_current_edge();
    declare_edges_list();

    // TODO: id
    //char prefix[30] = "";
    //current_edge->id = snprintf(prefix,"%s%s", source, dest);
    // source + dest + label
    current_edge->source = source;
    current_edge->dest = dest;
    current_edge->label = label;
    current_edge->pos_x = pos_x;
    current_edge->pos_y = pos_y;

    Edge *edge_to_add = copy_current_edge();
    add_edge(edge_to_add);
    init_current_edge();
}

void create_edge(char *source, char *dest, char *label) {
    declare_current_edge();
    declare_edges_list();

    //char prefix[30] = "";
    //current_edge->id = snprintf(prefix,"%s%s", source, dest);
    // source + dest + label
    current_edge->source = source;
    current_edge->dest = dest;
    current_edge->label = label;

    Edge *edge_to_add = copy_current_edge();
    add_edge(edge_to_add);
    init_current_edge();
}

void set_edge_color(char *color) {
    declare_current_edge();
    current_edge->color = color;
}

void set_path(char *path) {
    declare_current_edge();
    current_edge->path = path;
}