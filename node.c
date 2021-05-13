#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "node.h"

Node *current_node;
NodesList *nodes_list;

void init_current_node() {
    if (!current_node) {
        printf("INIT CURR NODE\n");
        current_node = malloc(sizeof(*current_node));
        clear_current_node();
    }
}

void clear_current_node(void) {
    current_node->id = "";
    current_node->pos_x = 0;
    current_node->pos_y = 0;
    current_node->label = "";
    current_node->color = "";
    current_node->bgcolor = "";
    current_node->size = 0;
    current_node->initial = "";
    current_node->fnl = "";
    current_node->next = NULL;
}

Node *copy_current_node(void) {
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
    printf("ID = %s, POS_X = %f, POS_Y = %f, LABEL = %s\n"
           "COLOR = %s, BGCOLOR = %s, SIZE = %f, INITIAL = %s, FINAL = %s\n\n",
           node->id, node->pos_x, node->pos_y, node->label, node->color, node->bgcolor,
           node->size, node->initial, node->fnl);
}

void print_nodes_list() {
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

void create_node(char *id, float pos_x, float pos_y) {
    init_current_node();
    if (!nodes_list) {
        nodes_list = malloc(sizeof(*nodes_list));
    }
    current_node->id = id;
    current_node->pos_x = pos_x;
    current_node->pos_y = pos_y;

    Node *node_to_add = copy_current_node();
    add_node(node_to_add);
    clear_current_node();

    print_nodes_list();
}

void set_label(char *label) {
    init_current_node();
    current_node->label = label;
}

void set_node_color(char *color) {
    init_current_node();
    current_node->color = color;
}

void set_bgcolor(char *bgcolor) {
    init_current_node();
    current_node->bgcolor = bgcolor;
}

void set_size(float size) {
    printf("SET SIZE\n");
    init_current_node();
    current_node->size = size;
}

void set_final(char *fnl) {
    init_current_node();
    current_node->fnl = fnl;
}

void choose_final_direction() {
    init_current_node();
    current_node->fnl = ""; // #TODO choose best direction
}

void set_initial(char *initial) {
    init_current_node();
    current_node->initial = initial;
}

void choose_initial_direction() {
    init_current_node();
    current_node->initial = ""; // #TODO choose best direction
}