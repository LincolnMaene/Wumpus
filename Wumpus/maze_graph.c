/*
 * This is the maze graph
 * @author: Lincoln D Maene
 */
#include "wumpus.h"
#include <stdio.h>
#include <stdlib.h>

int adjency_max_sizer=100;//maximum size of adjency list

Room * adjency_arr;

void destroy_chainr(Room*room);//destroys linked chains

void id_roomsr();//ids all the rooms


void create_roomr(int room_number){

    Room*creation_pointer;

    if(!adjency_arr)//if no space in memory is allocated yet
        allocate_adjency_listr();
    while(room_number>adjency_max_sizer-10)//if list is full
        reallocate_adjency_listr();
    
    creation_pointer=&adjency_arr[room_number];


    creation_pointer->existence=1;//the creation pointer conjures a room into existence 
       
    

}

int is_adjacentr(int src, int dest){//are two rooms adjecent

    int is_next=0;

    Room*adjacent_pointer=&adjency_arr[src];

    while(adjacent_pointer && !is_next){//while adjacent_pointer is not null and room has not been found
             
        adjacent_pointer=adjacent_pointer->next_room;

        if (adjacent_pointer->room_number==dest)
            is_next=1;
    }

    return is_next;

}

int allocate_adjency_listr(){//allocate space for adjecency_list

    int is_success=0;//don't be optimistic

    

    adjency_arr=malloc(adjency_max_sizer*sizeof(Room)); //array of adjency list
    adjency_arr->next_room = NULL;

    if(adjency_arr)
        is_success=1;
    
   

    id_roomsr();//id all the rooms
    return is_success;
    
}


void id_roomsr(){//ids all the rooms

    int counter;

    Room*id_pointer;

    for (counter=0; counter<adjency_max_sizer;counter++){

        id_pointer=&adjency_arr[counter];

        id_pointer->room_number=counter;
        id_pointer->existence=0;
    }       

}


int reallocate_adjency_listr(){//reallocate space for adjecency_list

    int is_success=0;//don't be optimistic
    adjency_max_sizer=2*adjency_max_sizer;

    adjency_arr=(Room*) realloc(adjency_arr, adjency_max_sizer*sizeof(Room)); //array of adjency list

    if(adjency_arr)
        is_success=1;

    return is_success;
    
}

int respawn_playerr(int room){//respawn the player into a given room

    int is_success=0; //don't be optimistic

    
    if (!room_existsr(room)) //if the room does not exist
        create_roomr(room);

    Room*respawn_pointer;//pointer to spawn room

    if (room_existsr(room)){

        respawn_pointer=&adjency_arr[room];
        respawn_pointer->player=1;
        is_success=1;
        }


    return is_success;

}

int respawn_wumpusr(int room){//respawn the wumpus into a given room

    int is_success=0; //don't be optimistic

    if (!room_existsr(room)) //if the room does not exist
        create_roomr(room);

    Room*respawn_pointer;//pointer to spawn room;//pointer to spawn room

    if (room_existsr(room)){
        respawn_pointer=&adjency_arr[room];
        respawn_pointer->wumpus=1;
        is_success=1;
        }

    

    return is_success;

}

Room * create_adjencyr(int src, int dest){//create a new adjecy relation

    if (src<0){
        printf("\nINVALID START ROOM, CANNOT BE LESS THAN 0\n");//if the src is invalid
        return;
    }

    
    if (!room_existsr(src)) //if the room does not exist
        create_roomr(src);

    if (!room_existsr(dest)) //if the room does not exist
        create_roomr(dest);

  
    Room * destination_pointer=&adjency_arr[src];//pointer which finds destination

    while (destination_pointer->next_room){//while the next room is not null

        destination_pointer=destination_pointer->next_room;


    }

    destination_pointer->next_room=malloc(sizeof(Room));
    destination_pointer->next_room->room_number=dest;

    destination_pointer->next_room->next_room = NULL;

    return destination_pointer->next_room;

}

int room_existsr(int room_number){

    int exists=1;//be optimistic, even though existence is quite weird, why is there something rather than nothing?

    if (!adjency_arr)//if the array itself does not exist
        exists=0;
    if (adjency_arr){

        if(!adjency_arr[room_number].existence)
            exists=0;
    }

    return exists;
}




int maximum_sizer(){//current maximum size of maze
    return adjency_max_sizer;
}

void print_mazer(){//exactly what it sounds like

        Room * x_pointer;//pointer accross x accis

        int y_counter;//pointer accross y axis

        if(adjency_arr){//if the map exists in memory

            for (y_counter=0;y_counter<maximum_sizer();y_counter++){
                
                if(room_existsr(y_counter)){

                    x_pointer=&adjency_arr[y_counter];
                    
                    printf("%d-->",x_pointer->room_number);//print the room before its adjacencies
                    
                    
                    while(x_pointer->next_room){//while a room exists
                       

                        printf("%d-->",x_pointer->next_room->room_number);///print next room

                         
                        x_pointer=x_pointer->next_room;//point to next room
                    }

                     printf("\n");

                }            
               
            
            } 
        }
        else{
            printf("\nThere is nothting to print\n");
        }
    
}

void destroy_everythingr(Room*room){//frees up all used memory
    Room * x_pointer;//pointer accross x accis

    int y_counter;//pointer accross y axis

        if(adjency_arr){//if the map exists in memory

            for (y_counter=0;y_counter<maximum_sizer();y_counter++){
                
                
                    x_pointer=&adjency_arr[y_counter];
                    
                                      
                    
                    if(x_pointer->next_room){//while a room exists
                       

                        destroy_chainr(x_pointer->next_room);
                    }

                                        
               
            
            }

        free(adjency_arr);

        }

    
}

void destroy_chainr(Room*room){//destroys linked chains

    if(!room->next_room){
        free(room);
        return;
    }

    destroy_chainr(room->next_room);

}