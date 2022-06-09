/*
 * This is the maze graph
 * @author: Lincoln D Maene
 */
#include "wumpus.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h> 
#include "Queue.h"
//seed random number generator


int is_search_duplicate(int room);

int adjency_max_size=100;//maximum size of adjency list

Room * adjency_arr;

queue_type * unvisited_rooms;//queue used in breadth first search to find distance btw rooms

int * visited_rooms;

int * duplicate_flag;

int * parent_flag;

int room_visited(int);//tells us a room has been visited before


int seeded=0;
int player_room=0;//room the player is in
int wumpus_room=0;//room the wumpus is in
int is_game_over=0;//tells us the game is over

int how_many_rooms=0;


int last_room=0;//room at the end of the world

void destroy_chain(Room*room);//destroys linked chains

void id_rooms();//ids all the rooms

int move_player(int room){//player moves to given room, if adjacent
    
    if (is_adjacent(player_room,room))//if the room is adjacent
        respawn_player(room);
    
    if (adjency_arr[room].bats){//if there are bats
        printf("\nSuddenly, a giant bat grabs you and by the time you escape, you fall into a different cave\n");
        respawn_player(random_room());
    }

    return player_room;
}

int move_wumpus(){//wumpus moves to a random room in the maze, returns room the wumpus moved to

    int random_rooms=random_room();

    int infinity_flag=0;//warns us of infinity loop

    while (!(infinity_flag>last_room) && !is_adjacent(wumpus_room,random_rooms))//while the random room is not adjacent to the wumpus
    {
       random_rooms=random_room();
       infinity_flag++;
    }

    if(!(infinity_flag>last_room))
        respawn_wumpus(random_rooms);
    else
    {
        random_rooms=0;
    }

       

    return random_rooms;

    
}

void create_room(int room_number){

    
    Room*creation_pointer;

    if(!adjency_arr)//if no space in memory is allocated yet
        allocate_adjency_list();
    while(room_number>adjency_max_size-10)//if list is full
        reallocate_adjency_list();
    
    creation_pointer=&adjency_arr[room_number];


    creation_pointer->existence=1;//the creation pointer conjures a room into existence 
    creation_pointer->pit=0;
    creation_pointer->bats=0;
       
    if(room_number>last_room)
			last_room=room_number;//update the last room

    how_many_rooms++;


}

int is_adjacent(int src, int dest){//are two rooms adjecent

    int is_next=0;
    Room*adjacent_pointer=NULL;
    if (room_exists(src)){
        adjacent_pointer=&adjency_arr[src];

        adjacent_pointer=adjacent_pointer->next_room;

    }

    

    while(adjacent_pointer && !is_next){//while adjacent_pointer is not null and room has not been found
        //printf("\nAdjacent pointer is at %d\n",adjacent_pointer->room_number);
        if (adjacent_pointer->room_number==dest)
            is_next=1;

         adjacent_pointer=adjacent_pointer->next_room;
    }

    return is_next;

}

int allocate_adjency_list(){//allocate space for adjecency_list

    int is_success=0;//don't be optimistic

    

    adjency_arr=malloc(adjency_max_size*sizeof(Room)); //array of adjency list

    if(adjency_arr)
        is_success=1;
    
   

    id_rooms();//id all the rooms
    return is_success;
    
}


void id_rooms(){//ids all the rooms

    int counter;

    Room*id_pointer;

    for (counter=0; counter<adjency_max_size;counter++){

        id_pointer=&adjency_arr[counter];

        id_pointer->room_number=counter;
        id_pointer->existence=0;
    }       

}


int reallocate_adjency_list(){//reallocate space for adjecency_list

    int is_success=0;//don't be optimistic
    adjency_max_size=2*adjency_max_size;

    adjency_arr=(Room*) realloc(adjency_arr, adjency_max_size*sizeof(Room)); //array of adjency list

    if(adjency_arr)
        is_success=1;

    id_rooms();//id all the rooms

    return is_success;
    
}

int respawn_player(int room){//respawn the player into a given room

    

    int is_success=0; //don't be optimistic

    
    if (!room_exists(room)) //if the room does not exist
        create_room(room);

    Room*respawn_pointer;//pointer to spawn room

    if (room_exists(room)){

        respawn_pointer=&adjency_arr[room];
        respawn_pointer->player=1;
        is_success=1;
        if(room_exists(player_room))//remove player from current location
            adjency_arr[player_room].player=0;
        player_room=room;
        }


    return is_success;

}

int respawn_wumpus(int room){//respawn the wumpus into a given room

    int is_success=0; //don't be optimistic

    if (!room_exists(room)) //if the room does not exist
        create_room(room);

    Room*respawn_pointer;//pointer to spawn room;//pointer to spawn room

    if (room_exists(room)){
        respawn_pointer=&adjency_arr[room];
        respawn_pointer->wumpus=1;
        is_success=1;
        if(room_exists(wumpus_room))//remove wumpus from current location
            adjency_arr[wumpus_room].wumpus=0;
        wumpus_room=room;
        }

    

    return is_success;

}

Room * create_adjency(int src, int dest){//create a new adjecy relation

    if (src<0){
        printf("\nINVALID START ROOM, CANNOT BE LESS THAN 0\n");//if the src is invalid
        return;
    }

    
    if (!room_exists(src)) //if the room does not exist
        create_room(src);

    if (!room_exists(dest)) //if the room does not exist
        create_room(dest);

  
    Room * destination_pointer=&adjency_arr[src];//pointer which finds destination

    while (destination_pointer->next_room){//while the next room is not null

        destination_pointer=destination_pointer->next_room;


    }

    destination_pointer->next_room=malloc(sizeof(Room));
    destination_pointer->next_room->room_number=dest;



    return destination_pointer->next_room;

}

int room_exists(int room_number){

    int exists=1;//be optimistic, even though existence is quite weird, why is there something rather than nothing?

    if (!adjency_arr)//if the array itself does not exist
        exists=0;
    if (adjency_arr){

        if(!adjency_arr[room_number].existence)
            exists=0;
    }

    return exists;
}




int maximum_size(){//current maximum size of maze
    return adjency_max_size;
}

void print_maze(){//exactly what it sounds like

        Room * x_pointer;//pointer accross x accis

        int y_counter;//pointer accross y axis

        if(adjency_arr){//if the map exists in memory

            for (y_counter=1;y_counter<maximum_size();y_counter++){
                
                if(room_exists(y_counter)){

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

void destroy_everything(Room*room){//frees up all used memory
    Room * x_pointer;//pointer accross x accis

    int y_counter;//pointer accross y axis

        if(adjency_arr){//if the map exists in memory

            for (y_counter=0;y_counter<maximum_size();y_counter++){
                
                
                    x_pointer=&adjency_arr[y_counter];
                    
                                      
                    
                    if(x_pointer->next_room){//while a room exists
                       

                        destroy_chain(x_pointer->next_room);
                    }

                                        
               
            
            }

        free(adjency_arr);

        }

    
}

void destroy_chain(Room*room){//destroys linked chains

    if(!room->next_room){
        free(room);
        return;
    }

    destroy_chain(room->next_room);

         
        

}

int random_room(){//returns a random room of the maze
    
    int random_rooms;

    if(!seeded){
        srand(time(NULL)); 
        seeded=1;
    }

    random_rooms = (rand() % (last_room - 1 + 1)) + 1; 

    while (!room_exists(random_rooms))//while the random room does not exist
    {
       random_rooms = (rand() % (last_room - 1 + 1)) + 1; 
    }
    

   
        return random_rooms;
    


}

void create_extra_danger(){//ADD bats and pits

    int random=random_room();//have random pointer

  

    adjency_arr[random].bats=1;

    printf("\nSuper-bats have nested in cave %d\n",random);

    random=random_room();//have random pointer

  
    adjency_arr[random].bats=1;

    printf("\nMore Super-bats have nested in cave %d\n",random);


    random=random_room();//have random pointer



    adjency_arr[random].pit=1;

    printf("\nA bottomless pit has appeared in cave %d\n",random);

    random=random_room();//have random pointer


    adjency_arr[random].pit=1;

    printf("\nAnother bottomless pit has appeared in cave %d\n",random);



}

int game_over(){
    return is_game_over;
}

int find_player(){//return player location

    return player_room;

}
int find_wumpus(){//return wumpus location

        return wumpus_room;
}


void print_adjacent(int room){//prints the adjacent rooms
    Room*room_pointer;//pointer to next room
    room_pointer=&adjency_arr[room];

    while (room_pointer->next_room)
    {
        printf("%d ",room_pointer->next_room->room_number);

        room_pointer=room_pointer->next_room;
    }
    

}

int cave_distance(int src, int dest){//returns distance between two caves using breadth first search

		int is_found=0;//don't be optimistic

        int distance=1;

        visited_rooms=malloc(2*last_room*sizeof(int));
        duplicate_flag=malloc(2*last_room*sizeof(int));
        parent_flag=malloc(2*last_room*sizeof(int));
        int filler;//fills array to avoid seg fault

        for (filler=0;filler<2*last_room;filler++){

                visited_rooms[filler]=0;
                duplicate_flag[filler]=0;
                parent_flag[filler]=-1;
        }
        
        if (src==dest){//if the src and dest are identical
            is_found=1;
            distance=0;

        }

        
        int visited_counter=0;
        int counter=0;
        //int flag_counter=0;//counter for duplicate flag

       		
		
        unvisited_rooms=queue_new();

        if (room_exists(src) && room_exists(dest)){//if both rooms exist

             queue_enqueue(unvisited_rooms,src);//enqueue the source

             parent_flag[src]=-1;

             while (!is_found){//while we haven't found the target          


               
                    for (counter=1;counter<last_room+1;counter++){//add every adjacent room to the queue


                        

                        
                        if(is_adjacent(queue_front(unvisited_rooms), counter) && !room_visited(counter)){//when the rooms is adjacent and not a duplicate add to queue
                             queue_enqueue(unvisited_rooms,counter);
                            
                            if (counter!=queue_front(unvisited_rooms))//only God can be his own parent!
                                parent_flag[counter]=queue_front(unvisited_rooms);//set the parent node
                            
                            if(counter==dest||!(unvisited_rooms->size)){//signal we have found target
                                  
                                  
                                is_found=1;

                               
                               

                            }                 
                              
                    

                        }

                    }

                        
                    if (!is_found){

                        if (unvisited_rooms->size){
                            visited_rooms[visited_counter]=queue_dequeue(unvisited_rooms);

                            visited_counter++;
                       }
                       else {

                          
                            is_found=1;

                       }

                
                
                    

                    }   

                        
            

            }

        }

        
        
        while (parent_flag[dest]!=src && parent_flag[dest]!=-1){//use the parent array to track down distance

                 dest=parent_flag[dest];
                 
                 distance++;

             }


        if (parent_flag[dest]==-1)//if the node is inaccessible
            distance=-1;
        

        if (src==dest){//if the src and dest are identical
            is_found=1;
            distance=0;

        }

         
          free(visited_rooms);
          free(duplicate_flag);
          free (parent_flag);
        return distance;
}

int room_visited(int room){

    int is_found=0;

    int counter=0;

    for (counter=0;counter<last_room+1;counter++){

            if(visited_rooms[counter]==room)
                is_found=1;
    }
    
    return is_found;

}

int is_search_duplicate(int room){

    int is_found=0;

    int counter=0;

    for (counter=0;counter<last_room+1;counter++){

            if(duplicate_flag[counter]==room)
                is_found=1;
    }
    
    return is_found;

}

int am_i_dead(){//check if player is alive

	int is_dead=0;

    
	if(cave_distance(find_wumpus(),find_player())<2 && cave_distance(find_wumpus(),find_player())>-1){

		printf("\nYou hear the most chilling scream of agony in your life. You blink. As your eyes open Charon, Hades' psychopomp--ferryman of the dead--welcomes you to the underworld\n");
		printf("\nThat's when you realize who screamed: the Wumpus has won the hunt\n");

		is_dead=1;
		is_game_over=1;
	}

    if(adjency_arr[find_player()].pit==1){
        printf("\nYou step on a bottomless pit and fall straight to Hades\nThe Wumpus has won the hunt\n");
        is_game_over=1;
        is_dead=1;
    }

	return is_dead;
}

int kill_wumpus(int killflag){//try to kill the wumpus
 
    int is_dead=0;   
    if (killflag<0){
        printf("\nThe wumpus is inacessible\n");
        printf("\nYou fire your only arrow. It whizzes and curves but nothing happens.\nThere is no hope. No escape.\n You are doomed, left to wander the maze aimlessly till the Wumpus finds you\n");
    }
    else if (killflag<3){

        printf("\nYou are a hero, hunter! As my champion (the Wumpus) dies, your World is saved. For now.\n");
        is_dead=1;
        

    }
    else{

        printf("\nYou fire your only arrow. It whizzes and curves but nothing happens.\nThere is no hope. No escape.\n You are doomed, left to wander the maze aimlessly till the Wumpus finds you\n");
    }

    is_game_over=1;

    return is_dead;

}


void track_wumpus(int flag){//give hints to wumpus location

    if(flag>4){

        printf("\nYou find no recent trace of the wumpus\n");
    }

    else if (flag==4){

        printf("\nFootsteps show the Wumpus was here, not too long ago\n");
    }
    else if (flag==3){

        printf("\nNot only are there tracks, but you begin to smell the Wumpus\n");
    }
    else if (flag<3){

        printf("\nThe wumpus' smell is overpowering! There are traces of its presence all around you. The beast is close.\n");
    }


}