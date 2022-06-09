/*
This is an Array implentation of the Queue
Author: Lincoln D Maene
*/
#include <stdlib.h>
#include <stdio.h>
#include "Queue.h"

queue_type * new_queue;//the new queue

/* create a new empty queue of intacters
   RETURN VALUE: a pointer to an queue upon success; NULL if failure */ 
queue_type *queue_new (void){

    


    new_queue=(queue_type*)malloc(sizeof(queue_type));//alloc memory for initial queue

       
    new_queue->front=-1;//new queue is empty
    new_queue->rear=-1;
    new_queue->size=0;

    new_queue->backing_array=(int*)malloc(sizeof(int)*5);

    new_queue->array_length=5;

    return new_queue;//return address of created queue

}

/* add a int onto an existing queue at the end
   RETURN VALUE: 0 upon success and -1 upon failure */
int queue_enqueue (queue_type * queue_point, int added_int){

    int success=-1;//assume failure

    
    

    if (queue_point->size==0){//if there is nothing in bring up the front
        queue_point->front=(queue_point->front)+1;

    }

    if (queue_point->size>queue_point->array_length-2){//give more memory as needed

        int * pointer_int=(int*) realloc(queue_point->backing_array,2*sizeof(int)*queue_point->array_length);

        queue_point->array_length=queue_point->array_length*2;
        
        queue_point->backing_array=pointer_int;

        
    }

    if (!(queue_point->size>queue_point->array_length-2)){//if no extra memory is needed,add element

        queue_point->rear=(queue_point->rear)+1;           

        queue_point->backing_array[queue_point->rear]=added_int;

        queue_point->size=(queue_point->size)+1;

        success=0;     

               
    }  

    if (success==-1)
        printf("QUEUE OVERFLOW!!!\n");
    
    return success;
}

/* Query the number of elements on a given queue. */ 
int queue_length (queue_type * queue){
    return queue->size;
}

/* remove the front int from a queue; queue_dequeue (s) can only be called if queue_length (s) > 0 */ 
int queue_dequeue (queue_type * queue){



    int success=-1;//assume queue is empty

    if (queue->size!=0){//if queue is not empty, dequeue

        success=queue->backing_array[queue->front];

        queue->front=queue->front+1;

        queue->size=queue->size-1;

    }

    if (queue->rear<queue->front)//if dequeue messes up the order
            queue->rear=queue->front;

    if (success==-1)
        printf("QUEUE UNDERFLOW!!!\n");


    return success;

}

/* return the front int from a queue without altering the queue; queue_front (s) can only be called if queue_length (s) > 0 */ 
int queue_front (queue_type *queue){

    int success=-1;//assume queue is empty

    if (queue->size!=0){//if queue is not empty, peek

        success=queue->backing_array[queue->front];

    }

    return success;


}

/* Free all memory associated with this queue. */ 
void queue_delete (queue_type *queue){
    
    free(queue->backing_array);  
    //free(queue); 
    
}

