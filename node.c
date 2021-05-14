#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "node.h"
#include "edge.h"

Node *current_node;
NodesList *nodes_list;
const char *INITIAL = "initial";
const char *FINAL = "final";

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
    current_node->type = "";
    current_node->direction = "";
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
    node_copy->type = current_node->type;
    node_copy->direction = current_node->direction;
    node_copy->next = current_node->next;
    return node_copy;
}

void print_node(Node *node) {
    printf("node %s {pos_x=%f, pos_y=%f, label=%s, color=%s, bgcolor=%s, size=%f, type=%s, direction=%s}\n",
           node->id, node->pos_x, node->pos_y, node->label, node->color, node->bgcolor, node->size, node->type,
           node->direction);
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

    declare_nodes_list();

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

        if (*current_node->direction == '\0') { // TODO : choose best direction
            if (strcmp(current_node->type, INITIAL) == 0) {
                current_node->direction = "west";
            } else if (strcmp(current_node->type, FINAL) == 0) {
                current_node->direction = "east";
            }
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

// TODO : move multiple
void move_all_nodes(float x_offset, float y_offset) {
    declare_nodes_list();

    Node *curr_node = nodes_list->first_node;

    while (curr_node != NULL) {
        curr_node->pos_x += x_offset;
        curr_node->pos_y += y_offset;
        curr_node = curr_node->next;
    }
}

void move_node(char *node_id, float x_offset, float y_offset) {
    declare_nodes_list();

    if (!node_exists(node_id)) {
        printf("ERROR : node %s doesn't exists.\n", node_id);
        return;
    }

    Node *curr_node = nodes_list->first_node;
    while (curr_node != NULL) {
        if (strcmp(curr_node->id, node_id) == 0) {
            curr_node->pos_x += x_offset;
            curr_node->pos_y += y_offset;
            curr_node = curr_node->next;
        }
    }
}

void rename_node(char *current_id, char *new_id) {
    declare_nodes_list();

    if (!node_exists(current_id)) {
        printf("ERROR : node %s doesn't exists.\n", current_id);
        return;
    }

    if (node_exists(new_id)) {
        printf("ERROR : node %s already exists.\n", new_id);
        return;
    }

    Node *curr_node = nodes_list->first_node;
    while (curr_node != NULL) {
        if (strcmp(curr_node->id, current_id) == 0) {
            curr_node->id = new_id;
        }
        curr_node = curr_node->next;
    }
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

void set_node_type(char *type) {
    declare_current_node();
    current_node->type = type;
}

void set_node_direction(char *direction) {
    declare_current_node();
    current_node->direction = direction;
}