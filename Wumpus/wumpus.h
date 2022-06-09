typedef struct node{

    int player;//detect player
    int wumpus;//detect wumpus
    int room_number;
    int existence;//do rooms exist?
    int pit;//is there a bottomless pit
    int bats;//are there super bats
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

int random_room();//returns the number of a random room of the maze

void create_extra_danger();//adds the pits and bats

int game_over();//tells us game is over

int move_player(int);//player moves to given room, if adjacent, returns room the player moved to
int move_wumpus();//wumpus moves to a random room in the maze, returns room the wumpus moved to, zero if wumpus cannot move
int find_player();//return player location
int find_wumpus();//return wumpus location

void print_adjacent(int );//prints the adjacent rooms

int cave_distance(int src, int dest);//returns distance between two caves

int am_i_dead();//check if player is dead

int kill_wumpus(int);//try to kill the wumpus

void track_wumpus();//gives hint to wumpus location