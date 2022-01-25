// Modify this file
// compile with: gcc linkedlist.c -o linkedlist

#include <stdio.h>
#include <stdlib.h> // contains the functions free/malloc

//define the struct node
typedef struct node{
	int year;
	int wins;
	struct node* next;
}node_t;

// TODO: Write your functions here
// There should be 1.) create_list 2.) print_list 3.) free_list
// You may create as many helper functions as you like.


//make new Node.
node_t* makeNode(int year, int wins, node_t* next){
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if (newNode == NULL){
		return NULL;
	}
	newNode->year = year;
	newNode->wins = wins;
	newNode->next = next;

	return newNode; 
}

//creat a linked list.
node_t* createList(node_t* iterator, int year, int wins){
	node_t* newNode = makeNode(year, wins, iterator);
	iterator = newNode;
	return iterator;

}

//print the list.
void printList(node_t* node){
	node_t* itr = node;
	while( itr != NULL){
		printf("%d, %d wins\n", itr->year, itr->wins);
		itr = itr->next;
	}
}

//free the list
void freeList(node_t* node){
	node_t* itr = node;
	if (node == NULL){
		return;
	}
	while (itr != NULL){
	 
	free(itr);
	itr = itr->next;
	}
}

int main(){
	
	//create nodes and link them
	node_t* year2014 = makeNode(2014, 71, NULL);
	node_t* year2015 = createList(year2014, 2015, 78);
	node_t* year2016 = createList(year2015, 2016, 93);
	node_t* year2017 = createList(year2016, 2017, 93);
	node_t* year2018 = createList(year2017, 2018, 108);
	
	printList(year2018);
 	freeList(year2018);

    return 0;
}
