// =================== Support Code =================
// Minimum Spanning Tree
//
// - Implement each of the functions to calculate a
//   minimum spanning tree.
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they 
//      should be removed from your final version)
// ==================================================
#ifndef MYMST_H
#define MYMST_H

#include <stdlib.h>
#include <assert.h>

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_dll.h"
#include "my_graph.h"
#include "my_pq.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.


// returns a doubly-linked list of graph edges that 
//    make up the minimimum spanning tree
// returns NULL on failure:
//   * if the graph is NULL
//   * if Kruskal's algorithm does not complete successfully
dll_t* calculate_mst(graph_t * g) {

	// TODO: Implement me!
	return NULL;
}

#endif