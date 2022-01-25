// =================== Support Code =================
// Linked Hashmap 
//
// - Implement each of the functions to create a working linked hashmap.
// - Do not change any of the function declarations
//   - (i.e. hashmap_t* hashmap_create() should not have additional arguments)
// - You should not have any 'printf' statements in your functions other 
//   than functions that explicitly ask for printf output. 
//   - (You may consider using these printf statements to debug,
//     but they should be removed from your final version)
// - You may add any helper functions that you think you need
//   (if any, or otherwise for debugging)
// ==================================================
#ifndef LINKED_HASHMAP_T
#define LINKED_HASHMAP_T

#include <stdlib.h>
#include <string.h>


// An entry consisting of a key-value pair.
// This is specifically for a (char*, char*) key-value pair
typedef struct pair {
    char* key;
    char* value;
} pair_t;

// Each node holds a key and a value
typedef struct node {
   
    //the hashmap node
    pair_t* kv;
    struct node* next;

    //the node for insertion DLL
    struct node* before;
    struct node* after;

} node_t;


// Simple hash function that will put a key into a bucket
// You should not modify this
int stringHash(char* myKey, int numberOfBuckets){
    return strlen(myKey) % numberOfBuckets;
}

// Create a function prototype to a function that takes
// in a char* and an int.
typedef int(*hashFunctionPointer)(char*, int); 

// Chained implementation of a hashmap
typedef struct hashmap {
    unsigned int buckets;  //the size of hashmap
    node_t** arrayOfLists; //the bucket array
    node_t* head;// the head node for DLL
    node_t* tail;// the tail node for DLL
    int count;  // the number of elements in DLL
    // A function pointer to a hash function
    // The hash_function must take in a 'char*' as a key, and have a
    // second parameter specifying the number of buckets.
    hashFunctionPointer hashFunction;
} hashmap_t;


//Create a new node
node_t* create_node(pair_t* kv, node_t* next, node_t* before, node_t* after){
    
     node_t* newNode = (node_t*)malloc(sizeof(node_t));
     if(newNode == NULL){
	exit(1);
     }

     newNode->kv = kv;
     newNode->next = next;
     newNode->before = before;
     newNode->after = after;
     return newNode;
}

// Creates a new hashmap
hashmap_t* hashmap_create(unsigned int _buckets) {
	
    hashmap_t* map = (hashmap_t*)malloc(sizeof(hashmap_t));
    
    //if we cannot allocate memory, it will return NULL;
    if (map == NULL){
    	return NULL;
    }
    
    //set the number of buckets;
    map->buckets = _buckets;
    
    //initilize the array;
    map->arrayOfLists = (node_t**)malloc(sizeof(node_t*)*_buckets);
    int i;
    for(i = 0; i <_buckets; i++){
	map->arrayOfLists[i] = NULL;
    }

    //set the head and tail node;
    map->head = NULL;
    map->tail = NULL;

    //set the num of elements
    map->count = 0;
 
    //point to hashFunction;
    map->hashFunction = stringHash;

    return map;
}

void free_node(node_t* node){
    if(node == NULL){
	return;
    }
    free(node->kv->key);
    free(node->kv->value);
    free(node->kv);
    free(node);
    node = NULL;
}


// Frees a hashmap
void hashmap_delete(hashmap_t* _hashmap) {
    //check if hashmap is NULL
    if(_hashmap == NULL){
	return;
    }
    
    //use DLL to free node
    node_t* temp = _hashmap->head; 
    while(temp != NULL){
	node_t* next = temp->after;
	free_node(temp);
	temp = next;
    }

    free(_hashmap->arrayOfLists);

    free(_hashmap);

}

// Returns a boolean value if a key has been put into
// the hashmap
//  - Returns a '1' if a key exists already
//  - Returns a '0' if the key does not exist
//  - Returns a '-9999' for invalid hashmaps
int hashmap_hasKey(hashmap_t* _hashmap, char* key) {
    //check if the hashmap is NLL
    if(_hashmap == NULL){
	return -9999;
    }

    unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
    node_t* iter = _hashmap->arrayOfLists[bucket];
    while(iter != NULL){
	if(strcmp(iter->kv->key, key) == 0){
		return 1;
	}
	iter = iter->next;
    }
    return 0;
}


// Insert a new key/value pair into a hashmap
void hashmap_insert(hashmap_t* _hashmap,char* key,char* value) {
    
    //check if the hashmap is NULL;
    if(_hashmap == NULL){
	return;
    }
    if(hashmap_hasKey(_hashmap, key) == 1){
	return;
    }

    //create new pair;
    pair_t* newpair = (pair_t*)malloc(sizeof(pair_t));
    newpair->key = (char*)malloc(strlen(key)*sizeof(char)+1);
    newpair->value = (char*)malloc(strlen(value)*sizeof(char)+1);
    
    //if we cannot alloc memory, the function will stop
    if(newpair == NULL || key == NULL || value == NULL){
	return;
    }


    //copy the string to key and value;
    strcpy(newpair->key, key);
    strcpy(newpair->value, value);

    //create a new node;
    node_t* newNode = create_node(newpair, NULL, NULL, NULL);

    unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);

    //make a head of linked list in array;
    node_t* iter = _hashmap->arrayOfLists[bucket];

    //iter will the newNode if it is empty;
    //else will find the end of link list and add the newNode;
    if(iter == NULL){
	_hashmap->arrayOfLists[bucket] = newNode;	
    }else{
	while(iter->next != NULL){
	iter = iter->next;
    	}
	iter->next = newNode;
	}
    //if no elements in the DLL, the head and tail is the newNode;
    if(_hashmap->count == 0){
	_hashmap->head = newNode;
	_hashmap->tail = newNode;
	_hashmap->count += 1;
    //the before and after is also newNode;
	newNode->before = NULL;
	newNode->after = NULL;
    }
    else{//there is element in the DLL
	_hashmap->tail->after = newNode;//connect the newNode by setting old tail after to newNode
	newNode->before = _hashmap->tail;//connect the newNode by setting newNode before to old tail
	_hashmap->tail = newNode;//set the newNode to tail
	_hashmap->count += 1;//adding 1 to count
	}
}

/*
// Insert a new key/value pair into a hashmap with Lexicographical order
void hashmap_insert(hashmap_t* _hashmap,char* key,char* value) {
    
    //check if the hashmap is NULL;
    if(_hashmap == NULL){
	return;
    }
    if(hashmap_hasKey(_hashmap, key) == 1){
	return;
    }

    //create new pair;
    pair_t* newpair = (pair_t*)malloc(sizeof(pair_t));
    newpair->key = (char*)malloc(strlen(key)*sizeof(char)+1);
    newpair->value = (char*)malloc(strlen(value)*sizeof(char)+1);
    
    //if we cannot alloc memory, the function will stop
    if(newpair == NULL || key == NULL || value == NULL){
	return;
    }

    //copy the string to key and value;
    strcpy(newpair->key, key);
    strcpy(newpair->value, value);

    //create a new node;
    node_t* newNode = create_node(newpair, NULL, NULL, NULL);

    unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);

    //make a head of linked list in array;
    node_t* iter = _hashmap->arrayOfLists[bucket];

    //iter will the newNode if it is empty;
    //else will find the end of link list and add the newNode;
    if(iter == NULL){
	_hashmap->arrayOfLists[bucket] = newNode;	
    }else{
	while(iter->next != NULL){
	iter = iter->next;
    	}
	iter->next = newNode;
    }
    
    //if no elements in the DLL, the head and tail is the newNode;
    if(_hashmap->count == 0){
	_hashmap->head = newNode;
	_hashmap->tail = newNode;
	_hashmap->count += 1;
    //the before and after is also newNode;
	newNode->before = NULL;
	newNode->after = NULL;
    }
    else{
	
	//there is element in the DLL
	if(strcmp(key,_hashmap->tail->kv->key)>0){
		//add the element to the end of DLL
		_hashmap->tail->after = newNode;//connect the newNode by setting old tail after to newNode
		newNode->before = _hashmap->tail;//connect the newNode by setting newNode before to old tail
		_hashmap->tail = newNode;//set the newNode to tail
		_hashmap->count += 1;//adding 1 to count
		return;
	}
	else if(strcmp(key,_hashmap->head->kv->key) < 0){
		//add the element to the front of DLL
		_hashmap->head->before = newNode;
		newNode->after = _hashmap->head;
		_hashmap->head = newNode;
		_hashmap->count += 1;
		return;
	}else{
		//insert in the middle of DLL
		node_t* iter = _hashmap->head;
		while(iter != NULL){
			if(strcmp(key, iter->kv->key) < 0){
				iter->before->after = newNode;
				newNode->before = iter->before;
				iter->before = newNode;
				newNode->after = iter;
				_hashmap->count += 1;
				return;
			}
			iter = iter->after;
		}
	}
    }
}
*/

//This is a helper function I added. When we know which node we should remove
//we also need to remove it from DLL
//this function will disconnect the node from DLL.
void remove_node(hashmap_t* _hashmap, node_t* node){
	
    //check if hashmap is empty 
    if(_hashmap == NULL){
	return;
    }
    //check if the node is NULL
    if(node == NULL){
	return;
    }
    if(strcmp(_hashmap->head->kv->key, node->kv->key) == 0){
	//this node is the head of the DLL
	if(_hashmap->count == 1){// the head is only one element in DLL
		free_node(node);
		_hashmap->head = NULL;
		_hashmap->count -= 1;
		return;
	}else{
		node->after->before = NULL;
		_hashmap->head = node->after;
		free_node(node);
		_hashmap->count -= 1;
		return;
	}
    }
    if(strcmp(_hashmap->tail->kv->key, node->kv->key) == 0){
	//this node is the tail of the DLL
	if(_hashmap->count == 1){
		free_node(node);
		_hashmap->tail = NULL;
		_hashmap->count -= 1;
		return;
	}else{
		node->before->after = NULL;
		_hashmap->tail = node->before;
		free_node(node);
		_hashmap->count -= 1;
		return;
	}
    }else{
	//the node is in the middle of DLL
	node->before->after = node->after; //break the connect with node
	node->after->before = node->before;
	free_node(node);
	_hashmap->count -= 1;
	return;
	}
}
 
// Return the first key-value pair in the ordering
//  - Returns NULL if there is no pair
pair_t* hashmap_getFirst(hashmap_t* _hashmap) {
    //check if the hashmap is NULL
    if(_hashmap == NULL){
	return NULL;
    }
    if(_hashmap->head == NULL){
	return NULL;
    }
    //return NULL if there is no element in the DLL
    if(_hashmap->count == 0){
	return NULL;
    }else{//return the kv from the head node
	pair_t* resultPair = (pair_t*)malloc(sizeof(pair_t));
   	resultPair->key = (char*)malloc(strlen(_hashmap->head->kv->key)*sizeof(char)+1);
    	resultPair->value = (char*)malloc(strlen(_hashmap->head->kv->value)*sizeof(char)+1);
    	strcpy(resultPair->key, _hashmap->head->kv->key);
	strcpy(resultPair->value, _hashmap->head->kv->value);
        return resultPair;
    }
	
}

// Return the last key-value pair in the ordering
//  - Returns NULL if there is no pair
pair_t* hashmap_getLast(hashmap_t* _hashmap) {
    //check if the hashmap is NULL
    if(_hashmap == NULL){
	return NULL;
    }
    if(_hashmap->tail == NULL){
	return NULL;
    }
    if(_hashmap->count == 0){
	return NULL;
    }else{//return the kv from the tail node
 	pair_t* resultPair = (pair_t*)malloc(sizeof(pair_t));
    	resultPair->key = (char*)malloc(strlen(_hashmap->tail->kv->key)*sizeof(char)+1);
    	resultPair->value = (char*)malloc(strlen(_hashmap->tail->kv->value)*sizeof(char)+1);
    	strcpy(resultPair->key, _hashmap->tail->kv->key);
	strcpy(resultPair->value, _hashmap->tail->kv->value);
        return resultPair;
    }
}

// Return a value from a key 
//  - Returns NULL if the key does not exist
char* hashmap_getValue(hashmap_t* _hashmap, char* key) {
    //check if the hashmap is NULL
    if(_hashmap == NULL){
	return NULL;
    }

    unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
    node_t* iter = _hashmap->arrayOfLists[bucket];
    if(iter == NULL){
	return NULL;
    }else{
	while(iter != NULL){
		if(strcmp(iter->kv->key, key) == 0){
			char* result = (char*)malloc(strlen(iter->kv->value)*sizeof(char)+1);
			strcpy(result, iter->kv->value); 
			return result;
		}
		iter = iter->next;
	}
	return NULL; //could not find the key;
    }
}

// Remove a key from a hashmap
void hashmap_removeKey(hashmap_t* _hashmap, char* key) {
     //check if the hashmap is NULL
     if(_hashmap == NULL){
	return;
     }

     unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
     node_t* iter = _hashmap->arrayOfLists[bucket];

     //if the array at [bucket] is NULL, the key does not exist
     //else will check the list from the iter to end
     if(iter == NULL){
	return;
     }

     //if the iter is not NULL

     //if the first node in list is match and there is only one node in the list;
     //remove node and set the position to NULL
     if(strcmp (iter->kv->key, key) == 0 && iter->next == NULL){
	_hashmap->arrayOfLists[bucket] = NULL;
	remove_node(_hashmap, iter);
	return;
     }

     node_t* temp = NULL;//temp is the node before iter
     while(iter !=NULL){

	//if the node in the middle of the list is the match
	if(strcmp(iter->kv->key, key) == 0 && temp != NULL){
		temp->next = iter->next;//disconnect the iter
		remove_node(_hashmap, iter);
		return;
	}
	//if the first node in list  is the match 
	if(strcmp(iter->kv->key, key) == 0 && temp == NULL){
		_hashmap->arrayOfLists[bucket] = iter->next;
		remove_node(_hashmap, iter);
		return;
	}
	temp = iter;
	iter = iter->next;
    }
    return; //cannot find the match, the key is not in the map	
}


// Update a key with a new Value
void hashmap_update(hashmap_t* _hashmap, char* key, char* newValue) {
    //check if the hashmap is NULL
    if(_hashmap == NULL){
	return;
    }
	
    unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
    node_t* iter = _hashmap->arrayOfLists[bucket];

    if(iter == NULL){
	return;
    }
    while(iter != NULL){
	if(strcmp(iter->kv->key, key) == 0){
		char* updateValue = (char*)malloc(strlen(newValue)*sizeof(char)+1);
		strcpy(updateValue, newValue); //copy the new value;
		free(iter->kv->value); //delete the old value;
		iter->kv->value = updateValue;
		return;
	}
	iter = iter->next;
    }
	return; //if the key does not exist;
}

// Prints all of the keys in a hashmap in order
void hashmap_printKeys(hashmap_t* _hashmap){
	if(_hashmap == NULL){
		return;
	}
	
	node_t* iter = _hashmap->head;
	while(iter != NULL){
		printf("Key: %s, Value: %s\n", iter->kv->key, iter->kv->value);
		iter = iter->after;
	}
	return;
}

#endif
