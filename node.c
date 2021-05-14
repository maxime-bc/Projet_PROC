#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "node.h"
#include "edge.h"

Node *current_node;
NodesList *nodes_list;

void declare_current_node() {
    if (!current_node) {
        current_node = malloc(sizeof(*current_node));
        init_current_node();
    }
}

void declare_nodes_list() {
    if (!nodes_list) {
        nodes_list = malloc(sizeof(*nodes_list));
    }
}

void init_current_node() {
    current_node->id = "";
    current_node->pos_x = 0;
    current_node->pos_y = 0;
    current_node->label = "";
    current_node->color = "";
    current_node->bgcolor = "";
    current_node->size = 30;
    current_node->initial = "west";
    current_node->fnl = "east";
    current_node->next = NULL;
}

Node *copy_current_node() {
    Node *node_copy = malloc(sizeof(*node_copy));
    node_copy->id = current_node->id;
    node_copy->pos_x = current_node->pos_x;
    node_copy->pos_y = current_node->pos_y;
    node_copy->label = current_node->label;
    node_copy->color = current_node->color;
    node_copy->bgcolor = current_node->bgcolor;
    node_copy->size = current_node->size;
    node_copy->initial = current_node->initial;
    node_copy->fnl = current_node->fnl;
    node_copy->next = current_node->next;
    return node_copy;
}

void print_node(Node *node) {
    printf("node %s {pos_x=%f, pos_y=%f, label=%s, color=%s, bgcolor=%s, size=%f, initial=%s, final=%s}\n",
           node->id, node->pos_x, node->pos_y, node->label, node->color, node->bgcolor, node->size, node->initial,
           node->fnl);
}

void print_nodes_list() {
    declare_nodes_list();
    Node *node = nodes_list->first_node;
    while (node != NULL) {
        print_node(node);
        node = node->next;
    }
}

void add_node(Node *new_node) {
    new_node->next = nodes_list->first_node;
    nodes_list->first_node = new_node;
}

void remove_node(const char *node_id) {
    int node_exists = 0;
    Node *prev_node, *curr_node;

    remove_edges_containing_node(node_id);
    curr_node = nodes_list->first_node;
    prev_node = curr_node;

    while (curr_node != NULL) {

        if (strcmp(curr_node->id, node_id) == 0) {
            node_exists = 1;
            if (prev_node == curr_node) {
                nodes_list->first_node = curr_node->next;
                free(curr_node);
            } else {
                prev_node->next = curr_node->next;
                free(curr_node);
            }
            break;
        }
        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    if (!node_exists) {
        printf("ERROR : Node %s doesn't exists.\n", node_id);
    }
}

void create_node(char *id, float pos_x, float pos_y) {
    declare_current_node();
    declare_nodes_list();

    if (node_exists(id)) {
        printf("ERROR : Node %s already exists.\n", id);
    } else {
        current_node->id = id;
        current_node->pos_x = pos_x;
        current_node->pos_y = pos_y;

        if (*current_node->label == '\0') {
            current_node->label = id;
        }

        Node *node_to_add = copy_current_node();
        add_node(node_to_add);
        init_current_node();
    }
}

int node_exists(char *node_id) {
    int node_exists = 0;
    Node *curr_node = nodes_list->first_node;

    while (curr_node != NULL) {
        if (strcmp(curr_node->id, node_id) == 0) {
            node_exists = 1;
            break;
        }
        curr_node = curr_node->next;
    }

    return node_exists;
}

void set_label(char *label) {
    declare_current_node();
    current_node->label = label;
}

void set_node_color(char *color) {
    declare_current_node();
    current_node->color = color;
}

void set_bgcolor(char *bgcolor) {
    declare_current_node();
    current_node->bgcolor = bgcolor;
}

void set_size(float size) {
    printf("SET SIZE\n");
    declare_current_node();
    current_node->size = size;
}

void set_final(char *fnl) {
    declare_current_node();
    current_node->fnl = fnl;
}

void choose_final_direction() {
    declare_current_node();
    current_node->fnl = ""; // #TODO choose best direction
}

void set_initial(char *initial) {
    declare_current_node();
    current_node->initial = initial;
}

void choose_initial_direction() {
    declare_current_node();
    current_node->initial = ""; // #TODO choose best direction
}