// =================== Support Code =================
// Graph.
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they 
//      should be removed from your final version)
// ==================================================
#ifndef MYSHORTEST_H
#define MYSHORTEST_H

#include <stdlib.h>
#include <assert.h>

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"
#include "my_pq.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.


// returns 1 if Dijkstra's algorithm completes successfully
// returns 0 if Dikjstra's algorithm does not complete successfully
// NOTE: Recall from our discussion, Dikjstra's algorithm does not
//       handle negative weight edges
// returns -1 if the graph is NULL
int calculate_shortest_path(graph_t * g, int source) {
	// TODO: Implement me!
	return -1;
}

// prints the shortest path from source to destination if there
// exists a path from the source to the destination. Consider
// how you can solve this recursively if you want to avoid using
// another data structure.
//
// Returns 1 if there is a path from source to destination
// Returns 0 if there is not a path from source to destination
// Returns -1 if the graph is NULL
// Returns -2 if called before `calculate_shortest_path` is called
// Note: consider the bookkeeping fields in `graph_t` struct to
//       determine whether this is true or not
int print_shortest_path(graph_t * g, int source, int dest) {
	// TODO: Implement me!
	return -1;
}

