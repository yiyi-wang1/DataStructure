// =================== Support Code =================
// Doubly Linked List ( DLL ).
//
//
//
// - Implement each of the functions to create a working DLL.
// - Do not change any of the function declarations
//   - (i.e. dll_t* create_dll() should not have additional arguments)
// - You should not have any 'printf' statements in your DLL functions. 
//   - (You may consider using these printf statements to debug,
//     but they should be removed from your final version)
//   - (You may write helper functions to help you debug your code such as print_list etc)
// ==================================================
#ifndef MYDLL_H
#define MYDLL_H

// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node {
	int data;
	struct node* next;
  	struct node* previous;
} node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL {
	int count;		// count keeps track of how many items are in the DLL.
	node_t* head;		// head points to the first node in our DLL.
   	node_t * tail;          // tail points to the last node in our DLL.
} dll_t;



//Creates a node
//Return a pointer to a newly created node.
//exit 1 if we could not allocate memory for node;
node_t* create_node(int data, node_t* next, node_t* previous){
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	newNode->data = data;
	newNode->next = next;
	newNode->previous = previous;
	return newNode;
}

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t* create_dll(){
	// Modify the body of this function as needed.
	dll_t* myDLL= NULL;	
	myDLL =(dll_t*)malloc(sizeof(dll_t));
	if (myDLL == NULL){
		return NULL;
	}
	myDLL->count = 0;
	myDLL->head = NULL;
	myDLL->tail = NULL;

	return myDLL;
}

// DLL Empty
// Check if the DLL is empty
// Returns -1 if the dll is NULL.
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
int dll_empty(dll_t* l){
	if(l == NULL){
		return -1;
	}
	if(l->count == 0){
		return 1;
	}
	else{
		return 0;
	}
}


// push a new item to the front of the DLL ( before the first node in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t* l, int item){
	if(l == NULL){
		return -1;
	}
	node_t* newHead = create_node(item, NULL, NULL);
	if(newHead == NULL){
		return 0;
	}
	if(l->count == 0){
		l->head = newHead;
		l->tail = newHead;
		l->count += 1;
		return 1;
	}
	else{
	l->head->previous = newHead;
	newHead->next = l->head;
	l->head = newHead;
	l->count += 1;
	return 1;
	}
}

// push a new item to the end of the DLL (after the last node in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t* l, int item){
	if(l == NULL){
		return -1; 
	}
	node_t* newTail = create_node(item, NULL, NULL);
	if(newTail == NULL){
		return 0;
	}
	if(l->count == 0){
		l->head = newTail;
		l->tail = newTail;
		l->count += 1;
		return 1;
	}
	else{
	l->tail->next = newTail;
	newTail->previous = l->tail;
	l->tail = newTail;
	l->count += 1;
	return 1;
	}
}


// Returns the first item in the DLL and also removes it from the list.
// Returns -1 if the DLL is NULL. 
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
int dll_pop_front(dll_t* t){
	
	if(dll_empty(t) == 1){
		return 0;
	}
	if(dll_empty(t) == -1){

		return -1;
	}
	else{
		node_t* temp = t->head;
		int removedItem = temp->data;
		//there is only 1 node in the DLL
		if(t->count == 1){
			free(temp);
			t->head = NULL;
			t->tail = NULL;
			t->count -= 1;
			return removedItem;	
		}else{
			temp->next->previous = NULL;
			t->head = temp->next;
			free(temp);
			t->count -= 1;
			return removedItem;
		}
	}
}


// Returns the last item in the DLL, and also removes it from the list.
// Returns a -1 if the DLL is NULL. 
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
int dll_pop_back(dll_t* t){

	if(dll_empty(t)== 1){
		return 0;
	}
	if(dll_empty(t)== -1){
		return -1;
	}
	else{
		node_t* temp = t->tail;
		int removedItem = temp->data;
		if(t->count == 1){
			free(temp);
			t->tail = NULL;
			t->head = NULL;
			t->count -= 1;
			return removedItem;	
		}else{
			temp->previous->next = NULL;
			t->tail = temp->previous;
			free(temp);
			t->count -= 1;	
			return removedItem;
		}
	} 	
}
	
// Inserts a new node before the node at the specified position.
// Returns -1 if the list is NULL
// Returns 1 on success
// Retruns 0 on failure:
//  * we couldn't allocate memory for the new node
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent as calling push_back).
int dll_insert(dll_t* l, int pos, int item){
	
	if(l == NULL){
		return -1;
	}	
	if(pos < 0){
		return 0;
	}
	if(pos > l->count -1){
		return 0;
	}
	//the first item should be at position 0, adding at pos 0 means push_front;
	if(pos == 0){
		return dll_push_front(l, item);
	}
	//the last item is size-1, so adding at the size means push_back;
	if(pos == l->count -1){
		return dll_push_back(l, item);
	}
	else{
		node_t* newNode = create_node(item, NULL, NULL);
		
		if(newNode == NULL){
			return 0;
		}	
		node_t* temp = l->head;
		int t = 0;
		//this is adding a node after so the position should be pos - 1;
		for (t = 0; t < pos - 1; t++){
			temp = temp->next;
		}
		newNode->next = temp->next;
		temp->next->previous = newNode;
		temp->next = newNode;
		newNode->previous = temp;
		l->count += 1;	
		return 1; // Note: This line is a 'filler' so the code compiles.
	}
}


// Returns the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the list is NULL
//  (does not remove the item)
// Returns 0 on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Assume no negative numbers in the list or the number zero.
int dll_get(dll_t* l, int pos){
	
	if(l == NULL){
		return -1;
	}
	if(l->count == 0){
		return -1;
	}
	if(pos < 0){
		return 0;
	}
	if(pos > l->count - 1){
		return 0;
	}
	if(pos == 0){
		return l->head->data;
	}
	if(pos == l->count - 1){
		return l->tail->data;
	} 
 	else{
		node_t* temp = l->head;
		int t = 0;
		for(t = 0; t< pos; t++){
			temp = temp->next;
		}
		int readItem = temp->data; 
		return readItem;
	}
	// Note: This line is a 'filler' so the code compiles.
}

// Removes the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the list is NULL
// Returns 0 on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Assume no negative numbers in the list or the number zero.
int dll_remove(dll_t* l, int pos){
	
	if(l == NULL){
		return -1;
	}
	if(pos < 0){
		return 0;
	}
	if(pos > l->count - 1){
		return 0;
	}
	if(pos == 0){
		return dll_pop_front(l);
	}
	if(pos == l->count - 1){
		return dll_pop_back(l);
	}
	else{
		node_t* temp = l->head;
		int t = 0;
		for(t = 0; t < pos; t++){
			 temp = temp->next;
		}
		temp->previous->next = temp->next;
		temp->next->previous = temp->previous;
		int removedItem = temp->data;
		free(temp);
		l->count -= 1;
		return removedItem;
	}	
}
	
// DLL Size
// Returns -1 if the DLL is NULL.
// Queries the current size of a DLL
int dll_size(dll_t* t){
	if(t == NULL){
		return -1;
	}
	int size = t->count;
	return size; // Note: This line is a 'filler' so the code compiles.
}

// Free DLL
// Removes a DLL and all of its elements from memory.
// This should be called before the proram terminates.
void free_dll(dll_t* t){
	if(t == NULL){
		return;
	}	
	node_t* temp = t->head;
	while(temp != NULL){
		node_t* next = temp->next;
		free(temp);
		temp = next;
	}
	free(t);

}

	

#endif
