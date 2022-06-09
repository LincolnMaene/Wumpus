#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wumpus.h"

int main()
{

	char parseString[1000] = "";
	int temp;
	int door, door_counter;
	char * ptr;
	int easy_mode=0;//which mode the player is in
	int tracker=0;

	int player_move;
	
	int begining_room;
	int wumpus_begin;
	int wumpus_distance; //how far from player wumpus is
	

	printf("Welcome to the Wumpus Cave, brave hunter.\n");
	printf("Please enter your commands in the format:\n");
	printf("<number> ( <list of comma-separated numbers> )\n");
	printf("Each on their own line.\n");
	printf("Enter  0 (0)  when finished with the cave.\n");

	do
	{
		scanf("%d (%[^)])", &temp, parseString);
		create_room(temp);
		
		

		printf("Cave room %d has exits: ", temp);

		// now parseString holds the values
		ptr = strtok(parseString, ",");
		door_counter = 0;

		while (ptr != NULL)
		{
			door = atoi(ptr); 
			create_adjency(temp, door);
			printf("%d ", door);
			door_counter++;
			ptr = strtok(NULL, ",");
		}
		if (door_counter == 0)
			printf("No Exits!\n");
		else
		{
			printf("exits\n");	
		}

	} while (temp > 0);

	printf("Well done! The hunt may begin!\n");	
	printf("\nBeware, you are not our only hunter today. The wumpus may move to hunt you, too\n");
	printf("In which cave would you like to begin?\nPlease enter the cave number: ");
	scanf("%d",&begining_room);

	while (!room_exists(begining_room)){//while the cave does not exist
		printf("\nThe cave does not exist, please reenter: \n");
		scanf("%d",&begining_room);
	}
	printf("\nWhere does the wumpus start?\nPlease enter the cave number: ");
	scanf("%d",&wumpus_begin);

	while (!room_exists(wumpus_begin)){
		printf("\nThe cave does not exist, please reenter: \n");
		scanf("%d",&wumpus_begin);
	}



	respawn_player(begining_room);	



	respawn_wumpus(wumpus_begin);

	wumpus_distance=cave_distance(find_player(),find_wumpus());

	tracker=wumpus_distance;
	

	
	printf("\nWould you, brave hunter, face bottomless pits, giant bats and a moving wumpus? Enter 0, if you dare, 1 if not: \n");
	scanf("%d",&easy_mode);

	while (!game_over() && easy_mode)//easy mode
	{

		printf("\n---------------------------------------------------------------------------------------\n");

		printf("You are in cave %d\nNear caves are: ",find_player());
		print_adjacent(find_player());

		printf("\nWhich cave would you like to move to next? You can also enter 0 to fire your arrow\n");

		scanf("%d",&player_move);

		
		if(!player_move)//if the player feels lucky
			kill_wumpus(wumpus_distance);
		if (!game_over()){

			move_player(player_move);
			am_i_dead();//check if player still breathes
				if (game_over())//if the player died
					continue;
			printf("\nThe wumpus is in %d\n",find_wumpus());

			wumpus_distance=cave_distance(find_player(),find_wumpus());
			if(wumpus_distance!=-1){//if wumpus is accessible
				track_wumpus(wumpus_distance);
			
				if(tracker>wumpus_distance){

					tracker=wumpus_distance;
					printf("\nYou are getting closer to the wumpus\n");
				}
				else if(tracker<wumpus_distance){

					tracker=wumpus_distance;
					printf("\nYou are getting further fromn the wumpus\n");
				}

				else {
					printf("\nYour distance from the wumpus has not changed\n");
				}

			}
			else 
					printf("\nWumpus is innacessible\n");
			am_i_dead();//check if player still breathes
				if (game_over())//if the player died
					continue;

		 

		}

			

	
		

		
	}

	if (!easy_mode)
		create_extra_danger();
	
	while (!game_over() && !easy_mode)//hard mode
	{

		

		printf("\n---------------------------------------------------------------------------------------\n");
		printf("You are in cave %d\nNear caves are: ",find_player());
		print_adjacent(find_player());

		printf("\nWhich cave would you like to move to next? You can also enter 0 to fire your arrow\n");

		scanf("%d",&player_move);

		
		if(!player_move)//if the player feels lucky
			kill_wumpus(wumpus_distance);
		if (!game_over()){

			move_player(player_move);
			am_i_dead();//check if player still breathes
				if (game_over())//if the player died
					continue;
				
				
			printf("\nThe wumpus is in %d\n",find_wumpus());

			wumpus_distance=cave_distance(find_player(),find_wumpus());
		
			if(wumpus_distance!=-1){//if wumpus is accessible
				track_wumpus(wumpus_distance);
			
				if(tracker>wumpus_distance){

					tracker=wumpus_distance;
					printf("\nYou are getting closer to the wumpus\n");
				}
				else if(tracker<wumpus_distance){

					tracker=wumpus_distance;
					printf("\nYou are getting further fromn the wumpus\n");
				}

				else {
					printf("\nYour distance from the wumpus has not changed\n");
				}

			}
			else 
					printf("\nWumpus is innacessible\n");
			am_i_dead();//check if player still breathes
				if (game_over())//if the player died
					continue;



			move_wumpus();//move wumpus
			printf("\nThe wumpus has moved to cave %d\n",find_wumpus());

			am_i_dead();//check if player still breathes
				if (game_over())//if the player died
					continue;

			wumpus_distance=cave_distance(find_player(),find_wumpus());
		
			if(!game_over()){//if the game continues
				track_wumpus(wumpus_distance);
			
				if(tracker>wumpus_distance){

					tracker=wumpus_distance;
					printf("\nYou are getting closer to the wumpus\n");
				}
				else if(tracker<wumpus_distance){

					tracker=wumpus_distance;
					printf("\nYou are getting further fromn the wumpus\n");
				}

				else {
					printf("\nYour distance from the wumpus has not changed\n");
				}



		}

		}

			

	
		

		
	}
	




	destroy_everything();//free memory

	return 0;
}


