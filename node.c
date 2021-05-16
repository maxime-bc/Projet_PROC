#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "node.h"
#include "edge.h"

Node *CURRENT_NODE = NULL;
NodesList *NODES_LIST = NULL;
IDList *IDS_LIST = NULL;
const char *INITIAL = "initial";
const char *FINAL = "final";

void declare_ids_list() {
    if (IDS_LIST == NULL) {
        IDS_LIST = malloc(sizeof(*IDS_LIST));
        IDS_LIST->first_id = NULL;
    }
}

void add_id(char *id) {
    declare_ids_list();

    Identifier *new_id = malloc(sizeof(*new_id));
    new_id->id = id;
    new_id->next = IDS_LIST->first_id;
    IDS_LIST->first_id = new_id;
}

void print_ids_list() {
    Identifier *current_id = IDS_LIST->first_id;

    while (current_id != NULL) {
        printf("ID %s\n", current_id->id);
        current_id = current_id->next;
    }
}

void move_multiple_nodes_by_id(float x_offset, float y_offset) {
    Identifier *current_id = IDS_LIST->first_id;

    while (current_id != NULL) {
        move_node(current_id->id, x_offset, y_offset);
        current_id = current_id->next;
    }
    IDS_LIST->first_id = NULL; // don't free
    //free_ids_list();
}

void free_ids_list() {
    Identifier *current_id = IDS_LIST->first_id;

    while (current_id != NULL) {
        IDS_LIST->first_id = current_id->next;
        free(current_id);
        current_id = IDS_LIST->first_id;
    }

    //IDS_LIST->first_id = NULL;

    printf("Printing remaining ids ??\n");
    print_ids_list();
}

void declare_current_node() {
    if (CURRENT_NODE == NULL) {
        CURRENT_NODE = malloc(sizeof(*CURRENT_NODE));
        init_current_node();
    }
}

void declare_nodes_list() {
    if (NODES_LIST == NULL) {
        NODES_LIST = malloc(sizeof(*NODES_LIST));
    }
}

void init_current_node() {
    CURRENT_NODE->id = "";
    CURRENT_NODE->pos_x = 0;
    CURRENT_NODE->pos_y = 0;
    CURRENT_NODE->label = "";
    CURRENT_NODE->color = "";
    CURRENT_NODE->bgcolor = "";
    CURRENT_NODE->size = 30;
    CURRENT_NODE->type = "";
    CURRENT_NODE->direction = "";
    CURRENT_NODE->next = NULL;
}

Node *copy_current_node() {
    Node *node_copy = malloc(sizeof(*node_copy));
    node_copy->id = CURRENT_NODE->id;
    node_copy->pos_x = CURRENT_NODE->pos_x;
    node_copy->pos_y = CURRENT_NODE->pos_y;
    node_copy->label = CURRENT_NODE->label;
    node_copy->color = CURRENT_NODE->color;
    node_copy->bgcolor = CURRENT_NODE->bgcolor;
    node_copy->size = CURRENT_NODE->size;
    node_copy->type = CURRENT_NODE->type;
    node_copy->direction = CURRENT_NODE->direction;
    node_copy->next = CURRENT_NODE->next;
    return node_copy;
}

void print_node(Node *node) {
    printf("node %s {pos_x=%f, pos_y=%f, label=%s, color=%s, bgcolor=%s, size=%f, type=%s, direction=%s}\n",
           node->id, node->pos_x, node->pos_y, node->label, node->color, node->bgcolor, node->size, node->type,
           node->direction);
}

void print_nodes_list() {
    declare_nodes_list();
    Node *node = NODES_LIST->first_node;
    while (node != NULL) {
        print_node(node);
        node = node->next;
    }
}

void add_node(Node *new_node) {
    new_node->next = NODES_LIST->first_node;
    NODES_LIST->first_node = new_node;
}

void remove_node(const char *node_id) {
    int node_exists = 0;
    Node *prev_node, *curr_node;

    declare_nodes_list();

    remove_edges_containing_node(node_id);
    curr_node = NODES_LIST->first_node;
    prev_node = curr_node;

    while (curr_node != NULL) {

        if (strcmp(curr_node->id, node_id) == 0) {
            node_exists = 1;
            if (prev_node == curr_node) {
                NODES_LIST->first_node = curr_node->next;
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
        CURRENT_NODE->id = id;
        CURRENT_NODE->pos_x = pos_x;
        CURRENT_NODE->pos_y = pos_y;

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

        Node *node_to_add = copy_current_node();
        add_node(node_to_add);
        init_current_node();
    }
}

int node_exists(char *node_id) {
    int node_exists = 0;
    Node *curr_node = NODES_LIST->first_node;

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

    Node *curr_node = NODES_LIST->first_node;

    while (curr_node != NULL) {
        curr_node->pos_x += x_offset;
        curr_node->pos_y += y_offset;
        curr_node = curr_node->next;
    }
}

void move_node(char *node_id, float x_offset, float y_offset) {
    declare_nodes_list();

    if (!node_exists(node_id)) {
        printf("ERROR : Node %s doesn't exists.\n", node_id);
        return;
    }

    Node *curr_node = NODES_LIST->first_node;
    while (curr_node != NULL) {
        if (strcmp(curr_node->id, node_id) == 0) {
            curr_node->pos_x += x_offset;
            curr_node->pos_y += y_offset;
        }
        curr_node = curr_node->next;
    }
}

void rename_node(char *current_id, char *new_id) {
    declare_nodes_list();

    if (!node_exists(current_id)) {
        printf("ERROR : Node %s doesn't exists.\n", current_id);
        return;
    }

    if (node_exists(new_id)) {
        printf("ERROR : Node %s already exists.\n", new_id);
        return;
    }

    Node *curr_node = NODES_LIST->first_node;
    while (curr_node != NULL) {
        if (strcmp(curr_node->id, current_id) == 0) {
            curr_node->id = new_id;
        }
        curr_node = curr_node->next;
    }
}

void set_label(char *label) {
    declare_current_node();
    CURRENT_NODE->label = label;
}

void set_node_color(char *color) {
    declare_current_node();
    CURRENT_NODE->color = color;
}

void set_bgcolor(char *bgcolor) {
    declare_current_node();
    CURRENT_NODE->bgcolor = bgcolor;
}

void set_size(float size) {
    printf("SET SIZE\n");
    declare_current_node();
    CURRENT_NODE->size = size;
}

void set_node_type(char *type) {
    declare_current_node();
    CURRENT_NODE->type = type;
}

void set_node_direction(char *direction) {
    declare_current_node();
    CURRENT_NODE->direction = direction;
}