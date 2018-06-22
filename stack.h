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

#include "list.h"
#include "graph.h"

#ifndef STACK_H
#define STACK_H

typedef struct stack Stack;

struct stack {
	List *items;
};

// Create a new stack and return its pointer
Stack *new_stack();

// Destroy a stack and its associated memory
void free_stack(Stack *stack);

// Push a new item of data onto the top of a stack. O(1).
void stack_push(Stack *stack, int data);

// Remove and return the top item of data from a stack. O(1).
// Error if the stack is empty (so first ensure stack_size() > 0)
int stack_pop(Stack *stack);

// Push a new item of data onto the end of a stack. O(1).
void stack_push_end(Stack *stack, int data);

// Remove and return the last item of data from a stack. O(1).
// Error if the stack is empty (so first ensure stack_size() > 0)
int stack_pop_end(Stack *stack);

// Return the number of items currently in a stack
int stack_size(Stack *stack);

#endif




