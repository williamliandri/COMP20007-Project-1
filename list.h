/* * * * * * * * *
 * 
 *
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * by William Liandri (728710) <wliandri@student.unimelb.edu.au>
 */
 
/* This program is cited from Week 3 Workshop by Matt Farrugia */

#include <stdbool.h>
#ifndef LIST_H
#define LIST_H

typedef struct list List;
typedef struct node Node;

// A list node points to the next node in the list, and to some data
struct node {
	Node *next;
	int data;
};

// A list points to its first and last nodes, and stores its size (num. nodes)
struct list {
	Node *head;
	Node *tail;
	int size;
};

// Create a new node and return its address
Node *new_node();

// Helper function to clear memory of a node
void free_node(Node *node);

// Create a new list and return a pointer to it
List *new_list();

// Destroy a list and free its memory
void free_list(List *list);

// Add an element to the front of a list
// This operation is O(1)
void list_add_start(List *list, int data);

// Add an element to the back of a list
// This operation is O(1)
void list_add_end(List *list, int data);

// Remove and return the front data element from a list
// This operation is O(1)
// Error if the list is empty (so first ensure list_size() > 0)
int list_remove_start(List *list);

// Remove and return the final data element in a list
// This operation is O(n), where n is the number of elements in the list
// Error if the list is empty (so first ensure list_size() > 0)
int list_remove_end(List *list);

// Return the number of elements contained in a list
int list_size(List *list);

// Returns whether the list contains no elements (true) or some elements (false)
bool list_is_empty(List *list);

#endif
