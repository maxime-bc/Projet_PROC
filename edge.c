#include <stdlib.h>
#include <stdio.h>
#include "edge.h"

Edge* current_edge;

void init_current_edge(){
    if(!current_edge){
        current_edge = malloc(sizeof(*current_edge));
    }
}

void create_edge_pos(char* source, char* dest, char* label, float pos_x, float pos_y){
    init_current_edge();
    printf("In create edge pos\n");
    //char prefix[30] = "";
    //current_edge->id = snprintf(prefix,"%s%s", source, dest);
    // source + dest + label
    current_edge->source = source;
    current_edge->dest = dest;
    current_edge->label = label;
    current_edge->pos_x = pos_x;
    current_edge->pos_y = pos_y;
}

void create_edge(char* source, char* dest, char* label){
    init_current_edge();
    printf("In create edge\n");
    //char prefix[30] = "";
    //current_edge->id = snprintf(prefix,"%s%s", source, dest);
    // source + dest + label
    current_edge->source = source;
    current_edge->dest = dest;
    current_edge->label = label;
}