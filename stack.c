/* * * * * * * * *
 * 
 *
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * by William Liandri (728710) <wliandri@student.unimelb.edu.au>
 */

/* This program is cited from Week 3 Workshop by Matt Farrugia with some 
modifications where I put 2 extra functions to insert the data at the end of 
the stack and to remove from the end of the stack */
 
#include <stdlib.h>
#include <assert.h>
#include "stack.h"	

// a stack is just a wrapper for a list of integers
// we will use the front of the list as the top of the stack (to take advantage
// of O(1) insert and remove operations)

/**************************** FUNCTION DEFINITIONS ***************************/

// Create a new stack and return its pointer
Stack *new_stack() {
	Stack *stack = malloc(sizeof *stack);
	assert(stack);

	stack->items = new_list();
	
	return stack;
}

// Destroy a stack and its associated memory
void free_stack(Stack *stack) {
	assert(stack != NULL);
	// Free the list of items, and the stack itself
	free_list(stack->items);
	free(stack);
}

// Push a new item of data onto the top of a stack. O(1).
void stack_push(Stack *stack, int data) {
	assert(stack != NULL);
	// the 'start' of the list will be our access point
	list_add_start(stack->items, data);
}

// Remove and return the top item of data from a stack. O(1).
// Error if the stack is empty (so first ensure stack_size() > 0)
int stack_pop(Stack *stack) {
	assert(stack != NULL);
	assert(stack_size(stack) > 0);

	// The 'start' of the list will be our access point
	return list_remove_start(stack->items);
}

// Push a new item of data onto the end of a stack. O(1).
void stack_push_end(Stack *stack, int data) {
	assert(stack != NULL);
	// the 'end' of the list will be our access point
	list_add_end(stack->items, data);
	
}

// Remove and return the last item of data from a stack. O(1).
// Error if the stack is empty (so first ensure stack_size() > 0)
int stack_pop_end(Stack *stack) {
	assert(stack != NULL);
	assert(stack_size(stack) > 0);

	// The 'end' of the list will be our access point
	return list_remove_end(stack->items);
}

// Return the number of items currently in a stack
int stack_size(Stack* stack) {
	assert(stack != NULL);
	// Delegate straight to list size function
	return list_size(stack->items);
}


