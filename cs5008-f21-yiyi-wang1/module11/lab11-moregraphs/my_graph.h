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
#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "my_dll.h"
#include <stdlib.h>
#include <assert.h>
// Create a graph data structure
typedef struct graph{
    int numNodes;
    int numEdges;
    dll_t* nodes;     //an array of nodes storing all of our nodes.
} graph_t;

typedef struct graph_node{
    int data;
    int visited; //1 means visited; 0 means not visited;
    dll_t* inNeighbors;
    dll_t* outNeighbors;
} graph_node_t;

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
// Returns NULL if we cannot allocate memory.
graph_t* create_graph(){
    // Modify the body of this function as needed.
    graph_t* myGraph= malloc(sizeof(graph_t));
    myGraph->nodes = create_dll();
    myGraph->numEdges = 0;
    myGraph->numNodes = 0;
    return myGraph;
}

// Returns the node pointer if the node exists.
// Returns NULL if the node doesn't exist or the graph is NULL
graph_node_t* find_node(graph_t * g, int value){
    //if the graph is NULL;
    if(g == NULL){
	return NULL;
    }

    node_t* iter = g->nodes->head;

    while(iter != NULL){
	graph_node_t* temp = iter->data;
	if(temp->data == value){
		return temp;
	}
	iter = iter->next;
    }
    //if could not find the node
    return NULL;
}

//Return 1 if the node exists
//Return 0 if the node does not exist
//Return -1 if the dll is NULL
int dll_find_node(dll_t* l, int value){
	//if the DLL is NULL
	if(l == NULL){
		return -1;
	}
	
	node_t* iter = l->head;
	while(iter != NULL){
		graph_node_t* temp = iter->data;
		if(temp->data == value){
			return 1;
		}
		iter = iter->next;
	}

	//if the node does not exit
	return 0;
}

// Creates a graph node
// Note: This relies on your dll implementation.
graph_node_t * create_graph_node(int value){
    graph_node_t * graph_node = malloc(sizeof(graph_node_t));
    
    if ( graph_node == NULL ) return NULL;
    
    graph_node->data = value;
    graph_node->visited = 0;
    graph_node->inNeighbors = create_dll();
    graph_node->outNeighbors = create_dll();
    
    return graph_node;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node already exists )
// Returns -1 if the graph is NULL.
int graph_add_node(graph_t* g, int value){
    if ( g == NULL ) return -1;
    
    if (find_node(g, value) != NULL) return -1;
    
    graph_node_t * newNode = create_graph_node(value);
    if ( newNode == NULL ) return -1;
    
    assert(g->nodes);
    dll_push_back(g->nodes, newNode);
    g->numNodes++;
    
    return 1;
}

//Free the graph node
//Return if the node is null
void free_node(graph_node_t* node){
	if(node == NULL){
		return;
	}
	free_dll(node->inNeighbors);//need to free the in dll
	free_dll(node->outNeighbors);//need to free the out dll
	free(node);//free the node itself
	node = NULL;//point the node to NULL
}
	

//Remove the node in dll
//Assume the node must in the dll
//Return if the dll is null or the node is null
void dll_remove_node(dll_t* l, graph_node_t* node){
	if(l == NULL){
		return;
	}

	if(node == NULL){
		return;
	}
	
	int removeData = node->data;
        //if the node is the head of the dll
        graph_node_t* NodeInHead = l->head->data;
        if(NodeInHead->data == removeData){
		//use the pop_front function from dll
		dll_pop_front(l);
		return;
	}
	//if the node is the tail of the dll
	graph_node_t* NodeInTail = l->tail->data;

	if(NodeInTail->data == removeData){
		//use the pop_back function
		dll_pop_back(l);
		return;
	}else{
	     //if the node is in the middle of dll
	     //need to find the node and remove it
	     	node_t* iter = l->head;
		while(iter != NULL){
			graph_node_t* temp = iter->data; //the graph node in the DLL
			if(temp->data == removeData){
				iter->previous->next = iter->next;
				iter->next->previous = iter->previous;
				free(iter);
				l->count -= 1;
				iter = NULL;
				return;
			}
			iter = iter->next;
		}
	}
}

// Returns 1 on success
// Returns 0 on failure ( or if the node doesn't exist )
// Returns -1 if the graph is NULL.
int graph_remove_node(graph_t* g, int value){
    // The function removes the node from the graph along with any edges associated with it.
    // That is, this node would have to be removed from all the in and out neighbor's lists that countain it.
    //if the graph is null
    if(g == NULL){
	return -1;
    }

    //if the node doesn't exist
    if(find_node(g, value) == NULL){
	return 0;
    }
    
    graph_node_t* removeNode = find_node(g,value);
    node_t* iter = g->nodes->head;

    while(iter != NULL){
	graph_node_t* temp = iter->data;
	if(temp->data == value){
		//remove from the other nodes' out neighbors list;
		//go through its inNeighbors list so we know which graph nodes will have this node 
		node_t* iter2 = temp->inNeighbors->head;
		while(iter2 != NULL){
			graph_node_t* temp2 = iter2->data;
			dll_remove_node(temp2->outNeighbors, removeNode);
			g->numEdges--;
			iter2 = iter2->next;
		}
		//remove from the other nodes' inNeighbors list;
		//go through its outNeighbors list so we know which graph nodes will have this node
		node_t* iter3 = temp->outNeighbors->head;
		while(iter3 != NULL){
			graph_node_t* temp3 = iter3->data;
			dll_remove_node(temp3->inNeighbors, removeNode);
			g->numEdges--;
			iter3 = iter3->next;
		}
		//remove the node from nodes DLL in graph struct; 
		dll_remove_node(g->nodes, removeNode);
		free_node(removeNode);
		g->numNodes--;
		return 1;
	}
	iter = iter->next;
    }
    return 0;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist )
// Returns -1 if the graph is NULL.
int contains_edge( graph_t * g, int source, int destination){
    
    //if the graph is null
    if(g == NULL){
	return -1;
    }
  
    graph_node_t* sourceNode = find_node(g,source);
    graph_node_t* destinationNode = find_node(g, destination);
  
    //if the source or destination node does not exist
    if(sourceNode == NULL || destinationNode == NULL){
	return 0;
    }

    if(dll_find_node(sourceNode->outNeighbors, destination) == 1 && dll_find_node(destinationNode->inNeighbors, source) == 1){
	return 1;
    } 

    return 0; //could not find
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge already exists )
// Returns -1 if the graph is NULL.
int graph_add_edge(graph_t * g, int source, int destination){
    // The function adds an edge from source to destination but not the other way.
    // Make sure you are not adding the same edge multiple times.
    // Make sure you modify the in and out neighbors appropriatelly. destination will be an out neighbor of source.
    // Source will be an in neighbor of destination.

    //if the graph is null
    if(g == NULL){
	return -1;
    }
    
    graph_node_t* sourceNode = find_node(g,source);
    graph_node_t* destinationNode = find_node(g, destination);
  
    //if the source or destination node does not exist
    if(sourceNode == NULL || destinationNode == NULL){
	return 0;
    }

    //if the edge already exists
    if(contains_edge(g, source, destination) == 1){
	return 0;
    }

    //Add the source and destination into the dlls
    //Add destination to out dll of source node
    //Add source to in dll of destination node
    if(dll_push_back(sourceNode->outNeighbors, destinationNode) == 1 && dll_push_back(destinationNode->inNeighbors, sourceNode) == 1){
    	g->numEdges++;
	return 1;
    }else{
	return 0;
    }
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge doesn't exists )
// Returns -1 if the graph is NULL.
int graph_remove_edge(graph_t * g, int source, int destination){

    //The function removes an edge from source to destination but not the other way.
    //Make sure you remove destination from the out neighbors of source.
    //Make sure you remove source from the in neighbors of destination.
    
    //if the graph is null
    if(g == NULL){
	return -1;
    }
    
    graph_node_t* sourceNode = find_node(g,source);
    graph_node_t* destinationNode = find_node(g, destination);
  
    //if the source or destination node does not exist
    if(sourceNode == NULL || destinationNode == NULL){
	return 0;
    }

    //if the edge does not exists
    if(contains_edge(g, source, destination) == 0){
	return 0;
    }

    //Remove the destination graph node from the source's outNeighbor
    dll_remove_node(sourceNode->outNeighbors, destinationNode);

    //Remove the source graph node from the destination's inNeighbor
    dll_remove_node(destinationNode->inNeighbors, sourceNode);
  
    g->numEdges--;
    return 1;
}

// Returns dll_t* of all the in neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getInNeighbors( graph_t * g, int value ){
    //if the graph is null
    if(g == NULL){
	return NULL;
    }
	
    //get the node from graph
    graph_node_t* node = find_node(g, value);

    //if the node does not exist
    if(node == NULL){
	return NULL;
    }else{
	return node->inNeighbors;
    }
}

// Returns the number of in neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumInNeighbors( graph_t * g, int value){
    //if the graph is null
    if(g == NULL){
	return -1;
    }
	
    //get the node from graph
    graph_node_t* node = find_node(g, value);

    //call the dll_size function 
    return dll_size(node->inNeighbors);
}

// Returns dll_t* of all the out neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getOutNeighbors( graph_t * g, int value ){
    //if the graph is null
    if(g == NULL){
	return NULL;
    }
	
    //get the node from graph
    graph_node_t* node = find_node(g, value);

    //if the node does not exist
    if(node == NULL){
	return NULL;
    }else{
	return node->outNeighbors;
   }
}

// Returns the number of out neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumOutNeighbors( graph_t * g, int value){
    //if the graph is null
    if(g == NULL){
	return -1;
    }
	
    //get the node from graph
    graph_node_t* node = find_node(g, value);

    //call the dll_size function 
    return dll_size(node->outNeighbors);
}

// Returns the number of nodes in the graph
// Returns -1 if the graph is NULL.
int graph_num_nodes(graph_t* g){
    if(g == NULL){
	return -1;
    }
    return g->numNodes;
}

// Returns the number of edges in the graph,
// Returns -1 on if the graph is NULL
int graph_num_edges(graph_t* g){
    if(g == NULL){
	return -1;
    }
    return g->numEdges;
}

// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the program terminates.
// Make sure you free all the dll's too.
void free_graph(graph_t* g){

    //if the graph is NULL
    if(g == NULL){
	return;
    }
    //get the node from the graph
    node_t* iter = g->nodes->head;
    //
    while(iter != NULL){
	node_t* next = iter->next;
	graph_node_t* temp = iter->data; //get the graph node for each node
	free_node(temp);
	temp = NULL;
	free(iter);
	iter = next;
    }
    free(g->nodes);
    free(g);
}

//Reset the visited flag for all nodes in the graph
void reset_visited (graph_t* g){
    //if the graph is NULL
    if(g == NULL){
	return;
    }

    node_t* iter = g->nodes->head;

    while(iter != NULL){
	graph_node_t* temp = iter->data;
	temp->visited = 0;
	iter = iter->next;
    }
    return;
}


//Returns 1 if we can reach the destination from source
//Returns 0 if it is not reachable
//Returns -1 if the graph is NULL (using BFS)
int graph_is_reachable(graph_t* g, int source, int dest){
    if(g == NULL){
	return -1;
    }

    if(find_node(g,source) == NULL || find_node(g, dest) == NULL){
	return 0;
    }

    // use linked list to store the node(store the value) to visited
    dll_t* BFS = create_dll();
    if(BFS == NULL){
	return-1;
    }
    reset_visited(g);//reset the visited flag for all nodes;
    //add the start node at the end of the linked list
    dll_push_back(BFS,source);

    //when the linked list is not empty, will keep visit the node
    while(dll_empty(BFS)!= 1){
        //pop the first element in the BFS list
   	graph_node_t* temp = find_node(g, dll_pop_front(BFS));
	temp->visited = 1; //visited the node
	if(temp->data == dest){//if the node is dest, end the function
		free_dll(BFS);
		return 1;
        }//if not, add the outneighbors to BFS
    	node_t* iter = temp->outNeighbors->head;
    	while(iter!= NULL){
    		graph_node_t* temp2 = iter->data;
		if(temp2->visited == 0){//if the node is not visited;
			dll_push_back(BFS,temp2->data);
		
		}
		iter = iter->next;
	}
    }
    free_dll(BFS);
    return 0; //if the dest is not reachable	
}

//Returns 1 if there is a cycle in the graph
//Returns 0 if no cycles exist in the graph
//Returns -1 if the graph is NULL
int graph_has_cycle(graph_t* g){
    if(g == NULL){
	return -1;
    }
    dll_t* DFS = create_dll();
    if(DFS == NULL){
	return-1;
    }
    reset_visited(g);//reset the visited flag for all nodes;
    int numsVisited = 0;//the number of node visited;

    //add the node at the front of the linked list
    node_t* temp = g->nodes->head;
    
    //when the visited node is not equal to the number of nodes in graph
    while(numsVisited != graph_num_nodes(g)){
     	graph_node_t* start = temp->data;
     	dll_push_front(DFS,start->data);

	while(dll_empty(DFS)!= 1){
	
		//pop the first element in the  list
   		graph_node_t* temp2 = find_node(g, dll_pop_front(DFS));
		
		temp2->visited = 1; //visited the node
		numsVisited++; //add 1 to the number of visited;
	        //add the outneighbors to DFS
    		node_t* iter = temp2->outNeighbors->head;
    		while(iter!= NULL){
    			graph_node_t* temp3 = iter->data;
			if(temp3->visited == 0){//if the node is not visited;
				dll_push_back(DFS,temp3->data);
			}if(temp3->visited == 1){//if the node is already visited so there is a cycle
				free_dll(DFS);
				return 1;
			}
		iter = iter->next;
		}
    	}
	temp = temp->next;
    }
    free_dll(DFS);
    return 0; //if the graph has no cycle; 
}


void print_dll(dll_t* l){
	if(l == NULL){
		return;
	}
	node_t* iter = l->head;
	while(iter != NULL){
		int num = iter->data;
		printf("%d ", num);
		iter = iter->next;
	}
	return;
}


void graph_print_dfs(graph_t* g, int source, int dest, dll_t* path){
	graph_node_t* temp = find_node(g, source);
	temp->visited = 1;
	dll_push_back(path, source);
	
	if(source == dest){
		print_dll(path);
		return;
	}else{
	     node_t* iter = temp->outNeighbors->head;
	     while(iter != NULL){
		graph_node_t* temp2 = iter->data;
		if(temp2->visited == 0){
			graph_print_dfs(g, temp2->data, dest, path);
		}
		iter = iter->next;
	     }
	}
	dll_pop_back(path);//remove the node from path when reach the end of path but not destination
	//temp->visited = 0;
}

	
//Print any path from the source to the destination if there 
//exists a path from the source to the destination.
//Returns 1 if there is a path from source to destination
//Returns 0 if there is not a path from a source to destination
//Returns -1 if the graph is NULL
int graph_print_path(graph_t* g, int source, int dest){
    if(g == NULL){
	return -1;
    }
   
    if(graph_is_reachable(g,source,dest) == 0){
	return 0;
    }
    reset_visited(g); //reset the visited flag for all the nodes;   
    dll_t* result = create_dll();//use DLL to print the path;
    if(result == NULL){
	return -1;
    }
    graph_print_dfs(g,source,dest,result);
    free_dll(result);
    return 1;
 }



#endif
