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

//Test create the graph
int unitTest0(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	if(graph != NULL){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Test find node which is not exited in graph
int unitTest1(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	if(find_node(graph, 1) == NULL){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add node in graph
int unitTest2(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	if(find_node(graph,1)->data == 1){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add multiple nodes in graph
int unitTest3(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	int i = 0;
    	for(i = 0; i < 100; i++){
		graph_add_node(graph,i);
    	}

	if(graph_num_nodes(graph) == 100){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add one nodes multiple times in graph
int unitTest4(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	int i = 0;
    	for(i = 0; i < 100; i++){
		graph_add_node(graph,1);
    	}

	if(graph_num_nodes(graph) == 1){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Remove node in graph
int unitTest5(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_remove_node(graph,1);
	if(find_node(graph,1) == NULL){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add multiple nodes in graph
int unitTest6(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	int i = 0;
    	for(i = 0; i < 100; i++){
		graph_add_node(graph,i);
    	}
	for(i = 0; i < 100; i++){
		graph_remove_node(graph,i);
    	}
	if(graph_num_nodes(graph) == 0){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add edges in graph when source is not existed
int unitTest7(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	if(graph_add_edge(graph, 0, 1) == 0){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}
	
///Add edges in graph when destination is not existed
int unitTest8(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	if(graph_add_edge(graph, 1, 0) == 0){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add one edge in graph
int unitTest9(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_edge(graph, 1, 2);
	if(graph_num_edges(graph) == 1){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add edges in graph
int unitTest10(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 2, 1);
	if(graph_num_edges(graph) == 2){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add edges in graph
int unitTest11(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	int i;
    	for(i = 0; i < 100; i++){
		graph_add_node(graph,i);
		
    	}
	for(i = 0; i < 99; i++){
		graph_add_edge(graph, i, i+1);
	}
	if(graph_num_edges(graph) == 99){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add same edge multiple times in graph
int unitTest12(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	int i;
	for(i = 0; i < 100; i++){
		graph_add_edge(graph, 1, 2);
	}
	if(graph_num_edges(graph) == 1){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add edges in graph and test in Neighbors
int unitTest13(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_node(graph,3);
	graph_add_edge(graph,1,2);
	graph_add_edge(graph,1,3);
	if((getNumInNeighbors(graph,1) == 0) && (getNumInNeighbors(graph,2) == 1) &&(getNumInNeighbors(graph,3) == 1)){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add edges in graph and test out Neighbors
int unitTest14(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_node(graph,3);
	graph_add_edge(graph,1,2);
	graph_add_edge(graph,1,3);
	if((getNumOutNeighbors(graph,1) == 2) && (getNumOutNeighbors(graph,2) == 0) &&(getNumOutNeighbors(graph,3) == 0)){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add edges in graph and test in Neighbors
int unitTest15(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	int i;
    	for(i = 0; i < 100; i++){
		graph_add_node(graph,i);
		
    	}
	for(i = 0; i < 100; i++){
		graph_add_edge(graph, i, 0);
	}
	if(getNumInNeighbors(graph,0) == 100){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add edges in graph and test out Neighbors
int unitTest16(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	int i;
    	for(i = 0; i < 100; i++){
		graph_add_node(graph,i);
		
    	}
	for(i = 0; i < 100; i++){
		graph_add_edge(graph, 0, i);
	}
	if(getNumOutNeighbors(graph,0) == 100){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Remove edges in graph when source is not existed
int unitTest17(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	if(graph_remove_edge(graph, 0, 1) == 0){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}
	
//Remove edges in graph when destination is not existed
int unitTest18(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	if(graph_remove_edge(graph, 1, 0) == 0){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Remove edges in graph
int unitTest19(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	int i;
    	for(i = 0; i < 100; i++){
		graph_add_node(graph,i);
		
    	}
	for(i = 0; i < 99; i++){
		graph_add_edge(graph, i, i+1);
	}
	for(i = 0; i < 99; i++){
		graph_remove_edge(graph, i, i+1);
	}

	if(graph_num_edges(graph) == 0){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Remove same edge multiple times in graph
int unitTest20(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_edge(graph,1,2);
	int i;
	for(i = 0; i < 100; i++){
		graph_remove_edge(graph, 1, 2);
	}
	if(graph_num_edges(graph) == 0){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Remove edges in graph and test in Neighbors
int unitTest21(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_node(graph,3);
	graph_add_edge(graph,1,2);
	graph_add_edge(graph,1,3);
	graph_remove_edge(graph,1,3);
	if((getNumInNeighbors(graph,1) == 0) && (getNumInNeighbors(graph,2) == 1) &&(getNumInNeighbors(graph,3) == 0)){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Remove edges in graph and test out Neighbors
int unitTest22(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_node(graph,3);
	graph_add_edge(graph,1,2);
	graph_add_edge(graph,1,3);
	graph_remove_edge(graph,1,3);
	if((getNumOutNeighbors(graph,1) == 1) && (getNumOutNeighbors(graph,2) == 0) &&(getNumOutNeighbors(graph,3) == 0)){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Remove edges in graph and test in Neighbors
int unitTest23(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	int i;
    	for(i = 0; i < 100; i++){
		graph_add_node(graph,i);
		
    	}
	for(i = 0; i < 100; i++){
		graph_add_edge(graph, i, 0);
	}	
	for(i = 0; i < 100; i++){
		graph_remove_edge(graph, i, 0);
	}

	if(getNumInNeighbors(graph,0) == 0){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Remove edges in graph and test out Neighbors
int unitTest24(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	int i;
    	for(i = 0; i < 100; i++){
		graph_add_node(graph,i);
		
    	}
	for(i = 0; i < 100; i++){
		graph_add_edge(graph, 0, i);
	}
	for(i = 0; i < 100; i++){
		graph_remove_edge(graph, 0, i);
	}

	if(getNumOutNeighbors(graph,0) == 0){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add edges in graph and test remove node
int unitTest25(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	graph_add_node(graph,2);
	graph_add_node(graph,3);
	graph_add_edge(graph,1,2);
	graph_add_edge(graph,2,3);
	graph_remove_node(graph,2);
	if((getNumOutNeighbors(graph,1) == 0) && (getNumInNeighbors(graph,3) == 0) && graph_num_edges(graph)== 0){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Remove node which is not existed
int unitTest26(int status){
	int passed = 0;
	graph_t* graph = create_graph();
	graph_add_node(graph,1);
	if(graph_remove_node(graph,100) == 0){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//Add edges and remove node
int unitTest27(int status){
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
	graph_remove_node(graph,1);
	if((getNumInNeighbors(graph,2) == 0) && (getNumOutNeighbors(graph,2) == 1) && 
	   (getNumInNeighbors(graph,3) == 1) && (getNumOutNeighbors(graph,3) == 1) && 
	   (getNumInNeighbors(graph,4) == 1) && (getNumOutNeighbors(graph,4) == 0) && 
	   graph_num_edges(graph) == 2){
		passed = 1;
	}
	free_graph(graph);
	return passed;
}

//
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
	unitTest10,
	unitTest11,
	unitTest12,
	unitTest13,
	unitTest14,
	unitTest15,
	unitTest16,
	unitTest17,	
	unitTest18,
	unitTest19,
	unitTest20,
	unitTest21,
	unitTest22,
	unitTest23,
	unitTest24,
	unitTest25,
	unitTest26,
	unitTest27,

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

/*
    graph_t * graph = create_graph();
    graph_add_node(graph, 1);
    graph_add_node(graph, 1);
    graph_add_node(graph, 2);
    printf("total nodes: 2 == %d\n", graph_num_nodes(graph));
    graph_add_edge(graph,1,2);
    int result1 = getNumInNeighbors(graph,1);
    int result2 = getNumInNeighbors(graph,2);
    int result3 = getNumOutNeighbors(graph,1);
    int result4 = getNumOutNeighbors(graph,2);

    printf("Adding edge from 1 to 2\n");
    printf("1 inNeighbor: %d, outNeighbor: %d\n", result1,result3);
    printf("2 inNeighbor: %d, outNeighbor: %d\n", result2,result4);

    printf("========test=======\n");
    graph_add_node(graph,3);
    graph_add_node(graph,4);
    graph_add_node(graph,5);
    printf("total nodes: %d\n", graph_num_nodes(graph));
  
    graph_add_edge(graph,2,1);
    graph_add_edge(graph,1,3);
    graph_add_edge(graph,3,2);
    graph_add_edge(graph,4,3);
    graph_add_edge(graph,5,3);
    graph_add_edge(graph,5,4);
    printf("total edges: %d\n",graph_num_edges(graph));

    graph_remove_node(graph, 3);

    printf("total nodes: %d\n", graph_num_nodes(graph));
    printf("total edges: %d\n", graph_num_edges(graph));

    int i = 0;
    for(i = 0; i < 100; i++){
	graph_add_node(graph,i);
    }
    printf("total nodes: %d\n", graph_num_nodes(graph));
   
    for(i = 0; i< 100; i++){
	graph_remove_node(graph,i);
    }

     printf("total nodes: %d\n", graph_num_nodes(graph));
  
    printf("free graph now\n");
    free_graph(graph);
    return 0;
}
*/
