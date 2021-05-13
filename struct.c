#include <stdlib.h>
#include <stdio.h>
#include "struct.h"

Node* current_node;

void create_node(char* id, float pos_x, float pos_y){
    if(!current_node){
        current_node = malloc(sizeof(*current_node));
    }
    current_node->id = id;
    current_node->pos_x = pos_x;
    current_node->pos_y = pos_y;
    printf("Node %s\n", current_node->id); 
    return;
}

void set_label(char* label){
    if(!current_node){
        current_node = malloc(sizeof(*current_node));
    }
    current_node->label = label;
    return;
}