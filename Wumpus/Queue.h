struct queue;

struct queue
{
    int front;
    int rear;
    int size;
    int * backing_array;
    int array_length;
};

typedef struct queue queue_type;


/* create a new empty queue of intacters
   RETURN VALUE: a pointer to an queue upon success; NULL if failure */ 
queue_type *queue_new (void); 


/* add a int onto an existing queue at the end
   RETURN VALUE: 0 upon success and -1 upon failure */
int queue_enqueue (queue_type *, int); 


/* Query the number of elements on a given queue. */ 
int queue_length (queue_type *); 


/* remove the front int from a queue; queue_dequeue (s) can only be called if queue_length (s) > 0 */ 
int queue_dequeue (queue_type *); 


/* return the front int from a queue without altering the queue; queue_front (s) can only be called if queue_length (s) > 0 */ 
int queue_front (queue_type *); 


/* Free all memory associated with this queue. */ 
void queue_delete (queue_type *);
