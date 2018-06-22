/* * * * * * * * *
 * 
 *
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * by William Liandri (728710) <wliandri@student.unimelb.edu.au>
 */
 
/* This program is cited from Week 3 Workshop by Matt Farrugia */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "list.h"

/* * * *
 * FUNCTION DEFINITIONS
 */

// Create a new list and return a pointer to it
List *new_list() {
	List *list = malloc(sizeof *list);
	assert(list);
	
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;

	return list;
}

// Destroy a list and free its memory
void free_list(List *list) {
	assert(list != NULL);
	// Free each node
	Node *node = list->head;
	Node *next;
	while (node) {
		next = node->next;
		free_node(node);
		node = next;
	}
	// Free the list struct itself
	free(list);
}

// Create a new node and return its address
Node *new_node() {
	Node *node = malloc(sizeof *node);
	assert(node);
	
	return node;
}

// Helper function to clear memory of a node
void free_node(Node *node) {
	free(node);
}

// Add an element to the front of a list
// This operation is O(1)
void list_add_start(List *list, int data) {
	assert(list != NULL);

	// Create and initialise a new list node
	Node *node = new_node();
	node->data = data;
	node->next = list->head; // Next will be the old first node (may be null)

	// Place it at the start of the list
	list->head = node;

	// If list was empty, this new node is also the last node now
	if(list->size == 0) {
		list->tail = node;
	}

	// And we need to keep size updated!
	list->size++;
}

// Add an element to the back of a list
// This operation is O(1)
void list_add_end(List *list, int data) {
	assert(list != NULL);
	
	// We'll need a new list node to store this data
	Node *node = new_node();
	node->data = data;
	node->next = NULL; // As the last node, there's no next node

	if(list->size == 0) {
		// If the list was empty, new node is now the first node
		list->head = node;
	} else {
		// Otherwise, it goes after the current last node
		list->tail->next = node;
	}
	
	// Place this new node at the end of the list
	list->tail = node;
	
	// And keep size updated too
	list->size++;
}

// Remove and return the front data element from a list
// This operation is O(1)list
// Error if the list is empty (so first ensure list_size() > 0)
int list_remove_start(List *list) {
	assert(list != NULL);
	assert(list->size>0);
	
	Node *start_node = list->head;
	int data = start_node->data;
	
	// Then replace the head with its next node (may be null)
	list->head = list->head->next;

	// If this was the last node in the list, the tail also needs to be cleared
	if(list->size == 1) {
		list->tail = NULL;
	}

	// The list is now one node smaller
	list->size--;

	// and we're finished with the node holding this data
	free_node(start_node);

	// done!
	return data;
}

// Remove and return the final data element in a list
// This operation is O(n), where n is the number of elements in the list
// Error if the list is empty (so first ensure list_size() > 0)
int list_remove_end(List *list) {
	assert(list != NULL);
	assert(list->size > 0);
	
	// We'll need to save the data to return it
	Node *end_node = list->tail;
	int data = end_node->data;
	
	// Then replace the tail with the second-last node (may be null)
	// (to find this replacement, we'll need to walk the list --- the O(n) bit
	Node *node = list->head;
	Node *prev = NULL;
	while (node->next) {
		prev = node;
		node = node->next;
	}
	list->tail = prev;
	
	if(list->size == 1) {
		// If we're removing the last node, the head also needs clearing
		list->head = NULL;
	} else {
		// Otherwise, the second-last node needs to drop the removed last node
		prev->next = NULL;
	}

	// The list just got one element shorter
	list->size--;

	// we're finished with the list node holding this data
	free_node(end_node);

	// done!
	return data;
}

// Return the number of elements contained in a list
int list_size(List *list) {
	assert(list != NULL);
	return list->size;
}

// Returns whether the list contains no elements (true) or some elements (false)
bool list_is_empty(List *list) {
	assert(list != NULL);
	return (list->size==0);
}