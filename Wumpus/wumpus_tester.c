#include "wumpus.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    int counter;

    Room* player_pointer;

    Room* wumpus_pointer;

    int allocation_tester=-1;
    int reallocation_tester=-1;
        
    allocation_tester=allocate_adjency_list();

    reallocation_tester=reallocate_adjency_list();

    printf("\n---------------------------------------------------------------------------------\n");//test memory allocation
    printf("---------------------------------------------------------------------------------\n");//test memory allocation
    printf("\nTesting memory allocation: %d\n",allocation_tester);//test memory allocation
    printf("\nTesting memory reallocation: %d\n",reallocation_tester);//test memory reallocation

    respawn_player(10);

    respawn_wumpus(20);

   

    wumpus_pointer=create_adjency(0, 20);

    player_pointer=create_adjency(0, 10);

    printf("\nThis should be room 10: %d\n",player_pointer->room_number);//test room number
    printf("\nThere should be a player here: %d\n",player_pointer->player);//test player respawn
    printf("\nThere should NOT be a wumpus here: %d\n",player_pointer->wumpus);

    printf("\nThis should be room 20: %d\n",wumpus_pointer->room_number);//test room number
    printf("\nThere should NOT be a player here: %d\n", wumpus_pointer->player);
    printf("\nThere should be be a wumpus here: %d\n",wumpus_pointer->wumpus);//test wumpus respawn

    create_room(1);
    create_room(3);
    create_room(4);
    create_room(7);
    create_room(9);
    
    printf("\nThe following 7 rooms should exist in the maze: %d,  %d,  %d,  %d,  %d,  %d,  %d \n", 1, 3, 4, 7, 9, 10, 20);//test room number

    printf("\nThe following rooms exist: ");//test room number

    for (counter=0;counter<maximum_size(); counter++){

        if (room_exists(counter))
            
            printf("%d ", counter);

    }

    printf("\n");

    print_maze();




    printf("\n---------------------------------------------------------------------------------\n");//test memory allocation
    printf("---------------------------------------------------------------------------------\n");//test memory allocation

    destroy_everything();
    return 0;
}