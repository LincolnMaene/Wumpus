#pragma once

typedef struct node{

    int player;//detect player
    int wumpus;//detect wumpus
    int room_number;
    int existence;//do rooms exist?
    struct node * next_room;//next room in adjency list
    

}Room;

int allocate_adjency_list();//allocate space for adjecency_list
int reallocate_adjency_list();//reallocate space for adjecency_list

int is_adjacent(int src, int dest);//are two rooms adjecent

void create_room(int room_number);//create a room

void destroy_everything();//frees up all used memory

int respawn_player(int room);//respawn the player into a given room

int respawn_wumpus(int room);//respawn the wunpus into a given room

int room_exists(int room_number);//does the room exist?

int maximum_size();//current maximum size of maze

Room * create_adjency(int src, int dest);//create new adjency relationship

void print_maze();//exactly what it sounds like