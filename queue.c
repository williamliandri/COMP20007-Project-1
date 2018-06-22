/* * * * * * * * *
 * 
 *
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * by William Liandri (728710) <wliandri@student.unimelb.edu.au>
 */
 
/* This program is cited from Week 3 Workshop by Matt Farrugia */

#include <assert.h>
#include <stdlib.h>
#include "queue.h"

// a Queue is just a wrapper for a list of its items
// we will use the back of the list as the entry point, and the front as the 
// exit point (to take advantage of O(1) insert and remove operations)

/*************************** FUNCTION DEFINITIONS ***************************/

// Create a new queue and return its pointer
Queue *new_queue() {
	Queue *queue = malloc(sizeof *queue);
	assert(queue);

	queue->items = new_list();
	
	return queue;
}

// Destroy a queue and its associated memory
void free_queue(Queue *queue) {
	assert(queue != NULL);
	// Free the list of items, and the queue itself
	free_list(queue->items);
	free(queue);
}

// Insert a new item at the back of a queue. O(1).
void queue_enqueue(Queue *queue, int data) {
	assert(queue != NULL);
	// use the back of the list as the entry point
	list_add_end(queue->items, data);
}

// Remove and return the item at the front of a queue. O(1).
// Error if the queue is empty (so first ensure queue_size() > 0)
int queue_dequeue(Queue *queue) {
	assert(queue != NULL);
	assert(queue_size(queue) > 0);

	// Use the front of the list as the exit point
	return list_remove_start(queue->items);
}

// Return the number of items currently in a queue
int queue_size(Queue *queue) {
	assert(queue != NULL);
	// Delegate straight to list size function
	return list_size(queue->items);
}

