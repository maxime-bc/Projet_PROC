#include <stdlib.h>
#include <stdio.h>
#include "node.h"

Node* current_node;

void init_current_node(){
    if(!current_node){
        current_node = malloc(sizeof(*current_node));
    }
}

void create_node(char* id, float pos_x, float pos_y){
    init_current_node();
    current_node->id = id;
    current_node->pos_x = pos_x;
    current_node->pos_y = pos_y;
    printf("Node %s\n", current_node->id); 
    return;
}

void set_label(char* label){
    init_current_node();
    current_node->label = label;
    return;
}

void set_color(char* color){
    init_current_node();
    current_node->color = color;
    return;
}

void set_bgcolor(char* bgcolor){
    init_current_node();
    current_node->bgcolor = bgcolor;
    return;
}

void set_size(float size){
    init_current_node();
    current_node->size = size;
    return;
}

void set_final(char* fnl){
    init_current_node();
    current_node->fnl = fnl;
    return;
}

void choose_final_direction(){
    init_current_node();
    current_node->fnl = ""; // #TODO choose best direction
    return;
}

void set_initial(char* initial){
    init_current_node();
    current_node->initial = initial;
    return;
}

void choose_initial_direction(){
    init_current_node();
    current_node->initial = ""; // #TODO choose best direction
    return;
}