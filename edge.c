#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "edge.h"
#include "node.h"

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
    printf("edge %s - %s {pos_x=%f, pos_y=%f, label=%s, color=%s, path=%s}\n",
           edge->source, edge->dest, edge->pos_x, edge->pos_y, edge->label, edge->color, edge->path);
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

void remove_edge(char *source, char *dest) {
    int edge_exists = 0;
    Edge *prev_edge, *curr_edge;

    declare_edges_list();
    curr_edge = edges_list->first_edge;
    prev_edge = curr_edge;

    while (curr_edge != NULL) {

        if (strcmp(curr_edge->source, source) == 0 && strcmp(curr_edge->dest, dest) == 0) {
            edge_exists = 1;
            if (prev_edge == curr_edge) {
                edges_list->first_edge = curr_edge->next;
                free(curr_edge);
            } else {
                prev_edge->next = curr_edge->next;
                free(curr_edge);
            }
            break;
        }
        prev_edge = curr_edge;
        curr_edge = curr_edge->next;
    }

    if (!edge_exists) {
        printf("ERROR : Edge %s - %s doesn't exists.\n", source, dest);
    }
}

void remove_edges_containing_node(const char *node_id) {
    Edge *prev_edge, *curr_edge;

    declare_edges_list();
    curr_edge = edges_list->first_edge;
    prev_edge = curr_edge;

    while (curr_edge != NULL) {

        if (strcmp(curr_edge->source, node_id) == 0 || strcmp(curr_edge->dest, node_id) == 0) {

            if (prev_edge == curr_edge) {  // first element
                edges_list->first_edge = curr_edge->next;
                free(curr_edge);
                curr_edge = edges_list->first_edge;
                prev_edge = curr_edge;
            } else {
                prev_edge->next = curr_edge->next;
                free(curr_edge);
                curr_edge = prev_edge->next;
            }
        } else {
            curr_edge = curr_edge->next;
        }
    }
}


void create_edge_pos(char *source, char *dest, char *label, float pos_x, float pos_y) {
    declare_current_edge();
    declare_edges_list();

    declare_nodes_list();

    if (!node_exists(source)) {
        printf("ERROR : Node %s doesn't exists.\n", source);
    } else if (!node_exists(dest)) {
        printf("ERROR : Node %s doesn't exists.\n", dest);
    } else {
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
}

void create_edge(char *source, char *dest, char *label) {
    float pos_x = 0, pos_y = 0;
    // TODO: calcul des pos
    create_edge_pos(source, dest, label, pos_x, pos_y);
}


void set_edge_color(char *color) {
    declare_current_edge();
    current_edge->color = color;
}

void set_path(char *path) {
    declare_current_edge();
    current_edge->path = path;
}