// Include our header file for our my_bst.c
#include "my_bst.h"

// Include any other libraries needed
#include <stdio.h>
#include <stdlib.h>

// Creates a BST
// Returns a pointer to a newly created BST.
// The BST should be initialized with data on the heap.
// The BST fields should also be initialized to default values(i.e. size=0).
bst_t* bst_create(){
    // Modify the body of this function as needed.
    bst_t* myBST= NULL; 
    myBST = (bst_t*)malloc(sizeof(bst_t));

    if(myBST == NULL){
	return NULL;
    }
    myBST->root = NULL;
    myBST->size = 0;

    return myBST;
}

// BST Empty
// Check if the BST is empty
// Returns 1 if true (The BST is completely empty)
// Returns 0 if false (the BST has at least one element)
int bst_empty(bst_t* t){
    if(t == NULL){
	return 1;
    }
    if(t->size == 0){
	return 1;
    }else{
  	return 0;
    }
}

//createNode function
//create a new node with given data
bstnode_t* createNode(int item){	
    bstnode_t* newNode = (bstnode_t*)malloc(sizeof(bstnode_t));
    newNode->data = item;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

//addHelper function for adding newNode to Tree
//return 1 if the newNode is added;
//otherwise return 0;
int addHelper(bstnode_t* node, bstnode_t* newNode){
    //if the data is less than or equal to the current node
    if(newNode->data <= node->data){
	//if the node does not have left child, insert it
	if(node->leftChild == NULL){
		node->leftChild = newNode;
		return 1;
	}else{//if there is a left child, recursively call addHelper
		return addHelper(node->leftChild, newNode);
	}
    }//if the data is larger than the current node
    else if(newNode->data > node->data){
	//if the node does not have right child, insert it
	if(node->rightChild == NULL){
   		node->rightChild = newNode;
		return 1;
	}else{//if there is a right child, recursively call addHelper
		return addHelper(node->rightChild, newNode);
	}
    }
    return 0;
}

// Adds a new node containng item to the BST
// The item is added in the correct position in the BST.
//  - If the data is less than or equal to the current node we traverse left
//  - otherwise we traverse right.
// The bst_function returns '1' upon success
//  - bst_add should increment the 'size' of our BST.
// Returns a -1 if the operation fails.
//      (i.e. the memory allocation for a new node failed).
// Your implementation should should run in O(log(n)) time.
//  - A recursive imlementation is suggested.
int bst_add(bst_t* t, int item){
    if(t == NULL){
	return -1;
    }
    bstnode_t* newNode = createNode(item);
    //if we could not allocate for node
    if(newNode == NULL){
	return -1;
    }
    if(t->root == NULL){
	t->root = newNode;
	t->size += 1;
	return 1;
    }
    if(addHelper(t->root, newNode) == 1){
    	t->size +=1;
	return 1;
    }else{
	return -1;
    }	
}

//The helper function to print the tree in ascending order
void printHelper_ascending(bstnode_t* node){
	if(node == NULL){
		return;
	}
	if(node->leftChild != NULL){
		printHelper_ascending(node->leftChild);
	}
	printf("%d ", node->data);
	if(node->rightChild != NULL){
		printHelper_ascending(node->rightChild);
	}
}

//The helper function to print the tree in descending order
void printHelper_descending(bstnode_t* node){
	if(node == NULL){
		return;
	}
	if(node->rightChild != NULL){
		printHelper_descending(node->rightChild);
	}
	printf("%d ", node->data);
	if(node->leftChild != NULL){
		printHelper_descending(node->leftChild);
	}
}

// Prints the tree in ascending order if order = 0, 
// otherwise prints in descending order.
// A BST that is NULL should print "(NULL)"
// It should run in O(n) time.
void bst_print(bst_t *t, int order){
    if(NULL == t){
        printf("(NULL)");
    }else{
	if(order == 0){
		printHelper_ascending(t->root);
	}
	if(order == 1){
		printHelper_descending(t->root);
	}
    }
}

//The helper function to sum all elements in tree
int sumHelper(bstnode_t* node){
	int result = 0;
	if(node->leftChild != NULL){
		result = result + sumHelper(node->leftChild);
	}
	result = result + node->data;
	if(node->rightChild != NULL){
		result = result + sumHelper(node->rightChild);
	}
	return result;
}
		
// Returns the sum of all the nodes in the bst. 
// A BST that is NULL exits the program.
// It should run in O(n) time.
int bst_sum(bst_t *t){
	if(t == NULL){
		exit(0);
	}
	return sumHelper(t->root);
}


//The helper function to find data in tree
//Return 1 if the data is found;
//Otherwise return 0;
int findHelper(bstnode_t* node, int value){
	if(value == node->data){
		return 1;
	}
	if(value < node->data){
		if(node->leftChild != NULL){
			return findHelper(node->leftChild, value);
		}else{
			return 0;
		}
	}
	else if(value > node->data){
		if(node->rightChild != NULL){
			return findHelper(node->rightChild, value);
		}else{
			return 0;
		}
	}
	return 0;
}	

// Returns 1 if value is found in the tree, 0 otherwise. 
// For NULL tree -- exit the program. 
// It should run in O(log(n)) time.
int bst_find(bst_t * t, int value){
  if(t == NULL){
	exit(0);
  }
  return findHelper(t->root, value);
}

// Returns the size of the BST
// A BST that is NULL exits the program.
// (i.e. A NULL BST cannot return the size)
unsigned int bst_size(bst_t* t){
    if(t == NULL){
	exit(0);
    }
    return t->size;
}


//The free function to free the node and the children node;
void freeNode(bstnode_t* node){
	if(node == NULL){
		return;
	}
	freeNode(node->leftChild);
	freeNode(node->rightChild);
	free(node);
	node = NULL;
	return;
}


// Free BST
// Removes a BST and ALL of its elements from memory.
// This should be called before the proram terminates.
void bst_free(bst_t* t){
	if(t == NULL){
		return;
	}
	freeNode(t->root);
	free(t);
	return;
}


