#ifndef _QUEUE_H
#define _QUEUE_H

#include <mem_manager.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct queueADT * queue_t;

// creates a new queue
queue_t new_queue();
// add a element to queue
queue_t enqueue(queue_t queue, void * elem);
// removes element from queue and returns it
void * dequeue(queue_t queue);
// return first element of the queue
void * peek(queue_t queue);
// return size of the queue
size_t get_queue_size(queue_t queue);
// print queue 
void print_queue(queue_t queue, void (*print_func)(void * elem));
// removes an element and add it again
void requeue(queue_t queue);
// free de queue WATCH OUT FOR THE NODES, YOU NEED TO FREE THEM ONE BY ONE WITH DEQUEUE BECASE WE'RE NOT ALLOCATING THEM, IT'S YOUR JOB
void free_queue(queue_t queue);
// recibes a find function that return true if is the element we're searching for, and returns that elem if not returns NULL
void * find_queue(queue_t queue, int (*find_func)(void * elem));

#endif