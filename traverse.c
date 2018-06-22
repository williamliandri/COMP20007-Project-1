/* * * * * * * * *
 * 
 *
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * by William Liandri (728710) <wliandri@student.unimelb.edu.au>
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Use this library to use INT_MAX
#include <assert.h>
#include "traverse.h"
#include "graph.h"
#include "stack.h"
#include "queue.h"
#include "list.h"

#define VISITED 1 // Mark the town that has been visited
#define NOT_VISITED 0 // Mark the town that has not been visited
#define EMPTY_SIZE 0 // A constant for an empty size
#define NO_PARENT -1 // A constant to mark a vertex that does not have parent
#define AVAILABLE 1 // Mark the heap that is still available
#define NOT_AVAILABLE 0 // Mark the heap that is not available

/****************************** HELPER FUNCTIONS *****************************/
// Helper function to print the detailed path for part 3 output
void print_detailed_path(Stack *stack, Graph *graph);

// Helper function to find the distance from vertex id u to vertex id v
int find_distance(Graph *graph, int u, int v);

// Helper function to print the path
void print_path(Stack *stack, Graph *graph);

// Helper function to find the minimal distance from point u to v
int shortest_distance(Graph *graph, int *distance, int *heap);

// Helper function to store all of the parent edges from vertex u to vertex v
int store_parent_edges(Stack *stack, int *parent_edges);

/***************************** PART 1: PRINT_DFS *****************************/
void print_dfs(Graph* graph, int source_id) {
	Stack *temp;
	Edge *temp_edge;
	int *check_visited, current_vertex, total_visited = 0;
	temp = new_stack();
	
	// A dynamic array to check the visited and unvisited vertices
	check_visited = (int*)calloc(((graph->maxn)), sizeof(int));
	
	// Initialise the start town and push to the stack
	stack_push(temp, source_id);
	current_vertex = source_id;
	temp_edge = graph->vertices[current_vertex]->first_edge;
	
	while (stack_size(temp) > EMPTY_SIZE) {
		
		// CASE 1: Guard to break the loop (the loop will stop when all 
		// vertex have been visited)
		if (total_visited == graph->maxn) {
			stack_pop(temp);	
		}
		
		// CASE 2.1: The vertex has not been visited
		if (check_visited[current_vertex] == NOT_VISITED) {
			
			// Print the vertex, mark it as visited, and add up the total
			// visited by one
			printf("%s\n", graph->vertices[current_vertex]->label);
			check_visited[current_vertex] = VISITED;
			total_visited++;
			
			// CASE 2.2: The current vertex is not the start vertex
			if (current_vertex != source_id) {
				
				// Push the vertex to the stack
				stack_push(temp, current_vertex);	
			}
			
			// Update the current vertex to the next edge
			current_vertex = temp_edge->v;
			temp_edge = graph->vertices[current_vertex]->first_edge;
		}
		
		// CASE 3.1: The vertex has been visited and all of 
		// the vertices has not been visited
		else if (check_visited[current_vertex] == VISITED 
			&& total_visited != graph->maxn) {
		
			// Set the vertex with the last element on the stack and update
			// the temp_edge
			current_vertex = temp->items->head->data;
			temp_edge = graph->vertices[current_vertex]->first_edge;
			
			// CASE 3.2: Using while loop to iterate the vertex in order to 
			// find the edge that has not been visited
			while (check_visited[current_vertex] != NOT_VISITED) {
				
				// CASE 3.3: The next edge is not empty
				if (temp_edge->next_edge != NULL) {
					temp_edge = temp_edge->next_edge;
					
					// Update the current_vertex variable to find the next 
					// edge
					current_vertex = temp_edge->v;
				}
				
				// CASE 3.4: The next edge is empty
				else if (temp_edge->next_edge == NULL) {
					
					// Pop the stack and set the current vertex to the 
					// start element on the stack
					stack_pop(temp);
					current_vertex = temp->items->head->data;
					temp_edge = graph->vertices[current_vertex]->first_edge;
				}
			}
			
			// Update to store the current edge data
			temp_edge = graph->vertices[current_vertex]->first_edge;
		}	
	}
	
	// Free the list and the stack
	free_stack(temp);
	free(check_visited);
}

/***************************** PART 2: PRINT_BFS *****************************/
void print_bfs(Graph* graph, int source_id) {
	Queue *temp;
	Edge *temp_edge;
	int *check_visited, current_vertex, total_visited = 0;
	temp = new_queue();
	
	// A dynamic array to check the visited and unvisited vertices
	check_visited = (int*)calloc(((graph->maxn)), sizeof(int));
	
	// Initialise the start town and push to the queue
	current_vertex = source_id;
	temp_edge = graph->vertices[current_vertex]->first_edge;
	queue_enqueue(temp, current_vertex);
	
	while (queue_size(temp) > EMPTY_SIZE) {
		
		// CASE 1: All of the vertices have been visited
		if (total_visited == graph->maxn) {
			
			// Dequeue the data from the queue
			queue_dequeue(temp);
		}
		
		// CASE 2.1: The next edge is empty
		else if (temp_edge == NULL) {
			
			// Dequeue the data from the queue
			queue_dequeue(temp);

			// CASE 2.2: The current vertex has not been visited
			if (check_visited[current_vertex] == NOT_VISITED) {
				
				// Print the vertex, mark as visited, 
				// and add up the total visited by one
				printf("%s\n", graph->vertices[current_vertex]->label);
				check_visited[current_vertex] = VISITED;;
				total_visited++;
				
				// CASE 2.3: The current vertex is not the start vertex
				if (current_vertex != source_id) {
					
					// Enqueue the vertex to the queue
					queue_enqueue(temp, current_vertex);				
				}
			}
			
			// It will pop the queue and change temp_edge 
			// to the point on the next queue
			current_vertex = temp->items->head->data;
			temp_edge = graph->vertices[current_vertex]->first_edge;
		}
		
		// CASE 3.1: The vertex has not been visited
		else if (check_visited[current_vertex] == NOT_VISITED) {
			
			// Print the vertex, mark as visited, 
			// and enqueue it to the queue
			printf("%s\n", graph->vertices[current_vertex]->label);

			check_visited[current_vertex] = VISITED;
			total_visited++;
			
			// CASE 3.2: The current vertex is not the start vertex
			if (current_vertex != source_id) {
					
				// Enqueue the vertex to the queue
				queue_enqueue(temp, current_vertex);
			}
			
			// Update the current vertex to the next edge
			current_vertex = temp_edge->v;
			temp_edge = temp_edge->next_edge;
		}
		
		// CASE 4: The vertex has been visited
		else if (check_visited[current_vertex] == VISITED) {
			
			// Update the current vertex and the temp_edge to the next vertex
			current_vertex = temp_edge->v;
			temp_edge = temp_edge->next_edge;	
		}
	}
	
	// Free the memory
	free_queue(temp);
	free(check_visited);
}

/*************************** PART 3: DETAILED_PATH ***************************/
void detailed_path(Graph* graph, int source_id, int destination_id) {
	Stack *temp;
	Edge *temp_edge;
	int *check_visited, current_vertex, pop;
	temp = new_stack();
	
	// A dynamic array to check the visited and unvisited vertices
	check_visited = (int*)calloc(((graph->maxn)), sizeof(int));
	
	// Initialise the start town and push to the stack
	stack_push_end(temp, source_id);
	check_visited[source_id] = VISITED;
		
	// Set the current vertex as the first edge from the source id and
	// update the temp edge
	temp_edge = graph->vertices[source_id]->first_edge;
	current_vertex = temp_edge->v;
	
	
	while (current_vertex != destination_id) {
		
		// CASE 1.1: The current vertex has not been visited
		if (check_visited[current_vertex] == NOT_VISITED) {
				
			// Mark as visited and push it to the stack
			check_visited[current_vertex] = VISITED;
			stack_push_end(temp, current_vertex);
			
			// Update the datas to the first edge of 
			// the previous current vertex
			temp_edge = graph->vertices[current_vertex]->first_edge;
			current_vertex = temp_edge->v;
		}
		
		// CASE 2.1: The current vertex has been visited
		else if (check_visited[current_vertex] == VISITED) {
			
			// CASE 3.2: The next edge is not empty
			if (temp_edge->next_edge != NULL) {
				
				// Update the temp edge and the current vertex to the 
				// next edge
				temp_edge = temp_edge->next_edge;
				current_vertex = temp_edge->v;
			}
			
			// CASE 3.3: The next edge is empty
			else if (temp_edge->next_edge == NULL) {

				// Pop the last element on the stack and update 
				// the temp edge to the last element on the stack
				pop = stack_pop_end(temp);
				check_visited[pop] = VISITED;
				current_vertex = temp->items->tail->data;
				temp_edge = graph->vertices[current_vertex]->first_edge;
			}
		}
	}
	
	// Insert the destination id to the stack
	stack_push_end(temp, destination_id);
	
	// Print the detailed path
	print_detailed_path(temp, graph);
	
	// Free the memory
	free_stack(temp);
	free(check_visited);
}

/***************************** PART 4: ALL_PATHS *****************************/
void all_paths(Graph* graph, int source_id, int destination_id) {	
	Stack *temp;
	Edge *temp_edge;
	int *check_visited, current_vertex, pop, *is_all_edges, i;
	int first_path = 1, *parent_edges, total_parent_edges;
	int all_parents_visited = 1;
	
	// A dynamic array to check the visited and unvisited vertices
	check_visited = (int*)calloc(((graph->maxn)), sizeof(int));
	
	// A dynamic array to check whether all of the edges of a vertex has been
	// visited
	is_all_edges = (int*)calloc(((graph->maxn)), sizeof(int));
	is_all_edges[source_id] = 1;
		
	temp = new_stack();
	temp_edge = graph->vertices[source_id]->first_edge;

	// Initialise the parameters and push the source id to the stack
	stack_push(temp, source_id);
	check_visited[source_id] = VISITED;
	current_vertex = temp_edge->v;
	
	while (stack_size(temp) > EMPTY_SIZE) {
		
		// CASE 1.1: The start is also the destination id
		if (source_id == destination_id) {
			printf("%s\n", graph->vertices[source_id]->label);
			break;
		}
		
		// CASE 2.1: It has reached the destination
		if (current_vertex == destination_id) {
			
			// Print the path and mark the destination id as unvisited
			stack_push(temp, destination_id);
			print_path(temp, graph);
			stack_pop(temp);
			check_visited[destination_id] = NOT_VISITED;
			
			// CASE 2.1 The first path is found
			if (first_path == 1) {
				first_path = 0;
				
				// Store all the parent edges on a dynamic array and 
				// calculate the number of total parent edges
				parent_edges = (int*) calloc(stack_size(temp), 
					sizeof(int));
				total_parent_edges = store_parent_edges(temp, 
					parent_edges);
			}
			
			// CASE 2.3: The next edge is not empty
			if (temp_edge->next_edge != NULL) {
				
				// Update the temp edge to the next one, set the current
				// vertex and push it to the stack
				temp_edge = temp_edge->next_edge;
				current_vertex = temp_edge->v;
			}
			
			// CASE 2.4: The next edge is empty
			else if (temp_edge->next_edge == NULL) {
				
				// Pop the top element from the stack and mark as unvisited
				pop = stack_pop(temp);
				is_all_edges[pop] = 1;
				check_visited[pop] = NOT_VISITED;
				
				// Update the current vertex and the temp edge 
				// to the top element on the stack
				current_vertex = temp->items->head->data;
				temp_edge = graph->
				vertices[current_vertex]->first_edge;
				
				// CASE 2.5 Find the edge where the next edge of 
				// the current vertex u is the popped vertex
				while(temp_edge->v != pop) {
					temp_edge = temp_edge->next_edge;
					
					// The next edge is null, pop the top element from the 
					// stack and try to find it again
					if (temp_edge == NULL) {
						pop = stack_pop(temp);
						check_visited[pop] = NOT_VISITED;
						current_vertex = temp->items->head->data;
						temp_edge = graph->
						vertices[current_vertex]->first_edge;
					}
				}
			}
		}
		
		// CASE 3.1: The vertex has not been visited
		else if (check_visited[current_vertex] == NOT_VISITED) {
			
			// Push the vertex to the stack and mark as visited
			check_visited[current_vertex] = VISITED;
			stack_push(temp, current_vertex);
			
			// Update the temp edge and the current vertex
			temp_edge = graph->vertices[current_vertex]->first_edge;
			current_vertex = temp_edge->v;
		}
		
		// CASE 4.1: The vertex has been visited
		else if (check_visited[current_vertex] == VISITED) {
			
			// CASE 4.2: The next edge is not empty
			if (temp_edge->next_edge != NULL) {
				
				// Update the temp edge and the current vertex
				temp_edge = temp_edge->next_edge;
				current_vertex = temp_edge->v;
			}
			
			// CASE 4.3: The next edge is empty
			else if (temp_edge->next_edge == NULL) {
				
				// Pop the top element from the stack and mark as unvisited
				pop = stack_pop(temp);
				is_all_edges[pop] = 1;
				check_visited[pop] = NOT_VISITED;
				
				// Update the current vertex and the temp edge 
				// to the top element on the stack
				current_vertex = temp->items->head->data;
				temp_edge = graph->
				vertices[current_vertex]->first_edge;
				
				// Find the edge where the next edge of the current vertex
				// u is the popped vertex
				while(temp_edge->v != pop) {
					temp_edge = temp_edge->next_edge;
					
					// The next edge is null, pop the top element from the 
					// stack and try to find it again
					if (temp_edge == NULL) {
						pop = stack_pop(temp);
						check_visited[pop] = NOT_VISITED;
						current_vertex = temp->items->head->data;
						temp_edge = graph->
						vertices[current_vertex]->first_edge;
					}
				}
			}
		}
		
		// CASE 5.1: Guard to break the loop
		if (stack_size(temp) == 1 && temp_edge->u == source_id 
			&& temp_edge->next_edge == NULL) {
		
			// Check whether all of the parent edges and its neighbour has
			// been visited
			for (i = 0; i < total_parent_edges; i++) {
				
				// There is a parent edge that has not been visited, set
				// false for all_parents_visited variable
				if (is_all_edges[parent_edges[i]] == 0) {
					all_parents_visited = 0;	
				}
			}
			
			// All of the parent edges have been visited
			if (all_parents_visited == 1) {
				
				// Free the memory 
				free(is_all_edges);
				free(parent_edges);
				break;
			}
		}
		
	}
	
	// Free the memory
	free_stack(temp);
	free(check_visited);
}

/*************************** PART 5: SHORTEST_PATH ***************************/
void shortest_path(Graph* graph, int source_id, int destination_id) {	
	Stack *temp;
	Edge *temp_edge;
	Node *temp_node;
	int *distance, *heap, *parent, current_distance;
	int total_heap = 0, current_vertex, min_vertex, i;
	temp = new_stack();
	temp_node = new_node();
	
	// Set a memory allocation
	distance = calloc(graph->maxn, sizeof(int));
	heap = calloc(graph->maxn, sizeof(int));
	parent = calloc(graph->maxn, sizeof(int));
	
	// Initialise the distance as INT_MAX
	for (i = 0; i < graph->maxn; i++) {
		distance[i] = INT_MAX;
	}
	
	// Set the distance for the source id as 0 and the parent as NO_PARENT
	distance[source_id] = 0;
	parent[source_id] = NO_PARENT;
	
	// Find the shortest path for all vertices (looping as long as there is
	// heap that is still available)
	while (total_heap <= graph->maxn) {
		
		// Find the minimum distance that is still available in the heap
		min_vertex = shortest_distance(graph, distance, heap);
		
		// Mark the picked vertex as choosen and update the total heap that
		// is already picked
		heap[min_vertex] = 1;
		total_heap++;
		
		// Iterate through all of the vertices to update the distance from
		// a picked vertex
		for (current_vertex = 0; current_vertex < graph->maxn; 
			current_vertex++) {
			
			// Iterate through the edges of a vertex to check whether
			// min_vertex is reachable and giving minimum distance
			temp_edge = graph->vertices[current_vertex]->first_edge;
			while (temp_edge != NULL) {
			
				// Update the distance when the distance of a 
				// picked vertex when the sum up with the distance 
				// from picked vertex to current vertex is 
				// smaller than the current distance on the array 
				// distance, the heap is still available and it is 
				// reachable from the current vertex
				current_distance = distance[min_vertex] + temp_edge->weight;
				if (heap[current_vertex] == 0 && 
					temp_edge->v == min_vertex && 
					current_distance < 
					distance[current_vertex]) {
				
					// Set the parent of a vertex as the picked vertex and
					// update the distance
					parent[current_vertex] = min_vertex;
					distance[current_vertex] = current_distance;
				}
				
				temp_edge = temp_edge->next_edge;
			}
		}
	}
	
	// Insert the shortest path from source id to destination id to the stack
	current_vertex = destination_id;
	
	// Push the destination id to the stack and initialise the distance
	stack_push(temp, destination_id);
	
	// Push the path to the stack
	while (current_vertex != source_id) {
		 stack_push(temp, parent[current_vertex]);
		 current_vertex = parent[current_vertex];
	}
	
	// Print the path and the total distance
	temp_node = temp->items->head;
	while (temp_node != NULL) {
		
		// Print the destination with the total distance
		if (temp_node->next == NULL) {
			printf("%s (%dkm)\n", graph->vertices[temp_node->data]->label, 
				distance[destination_id]);	
		}
		
		else {
			printf("%s, ", graph->vertices[temp_node->data]->label);
		}
		temp_node = temp_node->next;
	}
	
	// Free the memory
	free_stack(temp);
	free_node(temp_node);
	free(distance);
	free(heap);
	free(parent);
}

/**************************** PRINT DETAILED PATH ****************************/
// Helper function to print the detailed path and return the total distance
// (need to be used in part 5)
void print_detailed_path(Stack *stack, Graph *graph) {
	Node *prev_temp_node, *temp_node;
	prev_temp_node = new_node();
	temp_node = new_node();
	prev_temp_node = stack->items->head;
	temp_node = stack->items->head;
	int total_distance = 0, temp_distance = 0;
	
	// Iterate each data on the stack and print the label and print the 
	// total distance from u to specified vertex
	while (temp_node->data != stack->items->tail->data) {
		temp_distance = find_distance(graph, prev_temp_node->data,
			temp_node->data);
		total_distance += temp_distance;
		printf("%s (%dkm)\n", graph->vertices[temp_node->data]->label,
			total_distance);
		prev_temp_node = temp_node;
		temp_node = temp_node->next;
	}
	
	// Print the destination
	temp_distance = find_distance(graph, prev_temp_node->data,
			temp_node->data);
	total_distance += temp_distance;
	printf("%s (%dkm)\n", graph->vertices[temp_node->data]->label, 
		total_distance);
}

/******************************* FIND DISTANCE *******************************/
// Helper function to find the distance from vertex id u to vertex id v
int find_distance(Graph *graph, int u, int v) {
	Edge *temp_edge;
	temp_edge = graph->vertices[u]->first_edge;
	int distance = 0;
	
	// CASE 1.1: vertex id u is the same as vertex id v, it means
	// the source id
	if (u == v) {
		return distance;	
	}
	
	// CASE 1.2: It is not the source id
	else {
		
		// Using a while loop to find the edge where vertex id u goes to
		// vertex id v
		while (temp_edge->v != v) {
			temp_edge = temp_edge->next_edge;
		}
		distance = temp_edge->weight;
	}
	
	return distance;
}

/******************************** PRINT PATH *********************************/
// Helper function to print the path for part 4 output
void print_path(Stack *stack, Graph *graph) {
	Node *temp_node;
	temp_node = new_node();
	temp_node = stack->items->head;
	int *path, index = 0, i;
	path = (int*) calloc(stack_size(stack), sizeof(int));
	
	// Put the data into the dynamic array
	while (temp_node->data != stack->items->tail->data) {
		path[index] = temp_node->data;
		temp_node = temp_node->next;
		index++;
	}
	
	// Put the last data into the dynamic array
	path[index] = temp_node->data;
	
	// Print the path
	for (i = index; i >= 0; i--) {
		
		// The destination is printed without a comma and a space
		if (i == 0) {
			printf("%s\n", graph->vertices[path[i]]->label);	
		}
		else {
			printf("%s, ", graph->vertices[path[i]]->label);
		}
	}
}

/**************************** SHORTEST DISTANCE ******************************/
// Helper function to find the shortest distance
int shortest_distance(Graph *graph, int *distance, int *heap) {
	int min = INT_MAX, min_index, i;
	
	// Choose the minimum distance as long as it is still available on
	// the heap
	for (i = 0; i < graph->maxn; i++) {
		if (heap[i] == 0 && distance[i] <= min) {
			min = distance[i];
			min_index = i;
		}
	}
	return min_index;
}

/**************************** STORE PARENT EDGES *****************************/
// Helper function to store all of the parent edges from vertex u to vertex v
int store_parent_edges(Stack *stack, int *parent_edges) {
	Node* temp_node;
	temp_node = new_node();
	int total_parent_edges = 0;
	
	temp_node = stack->items->head;
	
	// Iterate through the stack and insert the parent edge 
	// to a dynamic array
	while (temp_node != NULL) {
		parent_edges[total_parent_edges] = temp_node->data;
		temp_node = temp_node->next;
		total_parent_edges++;
	}
	
	return total_parent_edges;
}