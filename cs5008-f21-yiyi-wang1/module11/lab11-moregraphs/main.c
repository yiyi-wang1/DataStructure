// Compile this assignment with: gcc -Wall main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"


// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.


//Add edges and test reachable when there is a path
int unitTest0(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_node(graph,3);
	graph_add_node(graph,4);
	graph_add_edge(graph,1,2);
	graph_add_edge(graph,2,3);
	graph_add_edge(graph,3,4);
	if(graph_is_reachable(graph,1,4) == 1){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add edges and test reachable when there is no path
int unitTest1(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_node(graph,3);
	graph_add_node(graph,4);
	graph_add_edge(graph,1,2);
	graph_add_edge(graph,2,3);
	if(graph_is_reachable(graph,1,4) == 0){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add nodes and test reachable when the source and dest is not existed
int unitTest2(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_node(graph,3);
	graph_add_node(graph,4);
	graph_add_edge(graph,1,2);
	graph_add_edge(graph,2,3);
	graph_add_edge(graph,3,4);
	if(graph_is_reachable(graph,5,6) == 0){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add edges and find cycles when the graph has no cycle
int unitTest3(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_node(graph,3);
	graph_add_node(graph,4);
	graph_add_edge(graph,1,2);
	graph_add_edge(graph,2,3);
	graph_add_edge(graph,3,4);
	if(graph_has_cycle(graph) == 0){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add edges and find cycles when the graph has cycle
int unitTest4(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_node(graph,3);
	graph_add_node(graph,4);
	graph_add_edge(graph,1,2);
	graph_add_edge(graph,2,3);
	graph_add_edge(graph,3,4);
	graph_add_edge(graph,4,1);
	if(graph_has_cycle(graph) == 1){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add edges and find cycles when the graph has more than one cycles
int unitTest5(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_node(graph,3);
	graph_add_node(graph,4);
	graph_add_edge(graph,1,2);
	graph_add_edge(graph,2,3);
	graph_add_edge(graph,3,4);
	graph_add_edge(graph,4,1);
	graph_add_edge(graph,4,2);
	if(graph_has_cycle(graph) == 1){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add edges and find cycles when the first node(start node) is not connected with other
int unitTest6(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_node(graph,3);
	graph_add_node(graph,4);
	graph_add_edge(graph,4,2);
	graph_add_edge(graph,2,3);
	graph_add_edge(graph,3,4);
	if(graph_has_cycle(graph) == 1){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add edges and print path
int unitTest7(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_node(graph,3);
	graph_add_node(graph,4);
	graph_add_node(graph,5);
	graph_add_node(graph,6);
	graph_add_edge(graph,1,2);
	graph_add_edge(graph,2,3);
	graph_add_edge(graph,3,4);
	if(graph_print_path(graph,1,4) == 1){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add edges and print path when there is a cycle
int unitTest8(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_node(graph,3);
	graph_add_node(graph,4);
	graph_add_node(graph,5);
	graph_add_node(graph,6);
	graph_add_edge(graph,1,2);
	graph_add_edge(graph,2,3);
	graph_add_edge(graph,3,4);
	graph_add_edge(graph,2,1);
	if(graph_print_path(graph,1,4) == 1){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add edges and print path when the first path can not reach destination
int unitTest9(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_node(graph,3);
	graph_add_node(graph,4);
	graph_add_node(graph,5);
	graph_add_node(graph,6);
	graph_add_edge(graph,1,5);
	graph_add_edge(graph,5,6);
	graph_add_edge(graph,1,2);
	graph_add_edge(graph,2,1);
	graph_add_edge(graph,2,3);
	graph_add_edge(graph,3,4);
	if(graph_print_path(graph,1,4) == 1){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}


int (*unitTests[])(int)={
	unitTest0,
	unitTest1,
	unitTest2,
	unitTest3,
	unitTest4,
	unitTest5,
	unitTest6,
	unitTest7,
	unitTest8,
	unitTest9,
	NULL
};

int main(int argc, const char * argv[]) {
	unsigned int testPassed = 0;
	int counter = 0;
	while(unitTests[counter] != NULL){
		printf("==========unitTest %d=========\n",counter);
		if(1==unitTests[counter](1)){
			printf("passed test\n");
			testPassed++;
		}else{
			printf("Test failed\n");
		}
		counter++;
	}

	printf("%d of %d tests passed\n", testPassed, counter);
	return 0;
}

