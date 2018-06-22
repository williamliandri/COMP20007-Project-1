/* * * * * * * * *
 * 
 *
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * by William Liandri (728710) <wliandri@student.unimelb.edu.au>
 */
 
/* This program is cited from Week 3 Workshop by Matt Farrugia */

#include "list.h"
#include "graph.h"

#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue Queue;

struct queue {
	List *items;
};


// Create a new queue and return its pointer
Queue *new_queue();

// Destroy a queue and its associated memory
void free_queue(Queue *queue);

// Insert a new item of data at the back of a queue. O(1).
void queue_enqueue(Queue *queue, int data);

// Remove and return the item of data at the front of a queue. O(1).
// Error if the queue is empty (so first ensure queue_size() > 0)
int queue_dequeue(Queue *queue);

// Return the number of items currently in a queue
int queue_size(Queue *queue);

#endif


 



 
 