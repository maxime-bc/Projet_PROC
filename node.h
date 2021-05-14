#ifndef NODE_H
#define NODE_H

typedef struct Node Node;
struct Node {
    char *id;
    float pos_x;
    float pos_y;
    char *label;
    char *color;
    char *bgcolor;
    float size;
    char *initial;
    char *fnl;
    Node *next;
};

typedef struct NodesList NodesList;
struct NodesList {
    Node *first_node;
};

void declare_current_node();

void declare_nodes_list();

void init_current_node(void);

Node *copy_current_node(void);

void print_node(Node *node);

void print_nodes_list();

void add_node(Node *new_node);

void remove_node(const char *node_id);

void create_node(char *id, float pos_x, float pos_y);

int node_exists(char *node_id);

void move_all_nodes(float x_offset, float y_offset);

void move_node(char *node_id, float x_offset, float y_offset);

void set_label(char *label);

void set_node_color(char *color);

void set_bgcolor(char *bgcolor);

void set_size(float size);

void set_final(char *fnl);

void choose_final_direction();

void set_initial(char *initial);

void choose_initial_direction();

#endif