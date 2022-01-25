// =================== Support Code =================
// Hashmap 
//
// - Implement each of the functions to create a working hashmap.
// - Do not change any of the function declarations
//   - (i.e. hashmap_t* hashmap_create() should not have additional arguments)
// - You should not have any 'printf' statements in your functions other 
//   than functions that explicitly ask for printf output. 
//   - (You may consider using these printf statements to debug,
//     but they should be removed from your final version)
// - You may add any helper functions that you think you need
//   (if any, or otherwise for debugging)
// ==================================================
#ifndef MY_HASHMAP_T
#define MY_HASHMAP_T

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
    pair_t* kv; // key/value pair
    struct node* next;
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
    unsigned int buckets;   // i.e. size of the hashmap
    node_t** arrayOfLists;  // An array of linked lists for our buckets
                            // Read another way -- an array of node_t*

    // A function pointer to a hash function
    // The hash_function must take in a 'char*' as a key, and have a
    // second parameter specifying the number of buckets.
    hashFunctionPointer hashFunction;
} hashmap_t;

// Creates a new hashmap
// Allocates memory for a new hashmap.
// Initializes the capacity(i.e. number of buckets)
// The algorithm is:
//  - allocate memory for our hashmap
//  - set the number of buckets
//  - initialize our array of lists for each bucket
//  - setup our hash function to point to our stringHash function
//  - return new map that we have created
hashmap_t* hashmap_create(unsigned int _buckets) {
	
	//allocate memory for hashmap and check;
	hashmap_t* map = (hashmap_t*)malloc(sizeof(hashmap_t));
	if(map == NULL){
		return NULL;
	}
	
	//set the number of buckets;
	map->buckets = _buckets;
	
	//initialize the array;
	map->arrayOfLists = (node_t**)malloc(sizeof(node_t*)*_buckets);
	int i;
	for(i = 0; i < _buckets; i++){
		map->arrayOfLists[i] = NULL;
	}
	
	//point to the hashFunction;
	map->hashFunction = stringHash;

    return map;
}

void free_node (node_t* node){
	free(node->kv->key);
	free(node->kv->value);
	free(node->kv);
	free(node);
}

// Frees a hashmap
// Responsibility to free a hashmap that has been previously allocated.
// Must also free all of the chains in the hashmap
// This function should run in O(n) time
void hashmap_delete(hashmap_t* _hashmap) {
	if( _hashmap == NULL){
		return;
	}

	int i;
    	for(i = 0; i < _hashmap->buckets; i++){
		node_t* iter = _hashmap->arrayOfLists[i]; 
		while (iter != NULL){		
			
			node_t* temp = iter->next;
			free_node(iter);
			iter = temp;
		}
	
	}
	//free the array;
	free(_hashmap->arrayOfLists);
    	//free hashmap; 
   	free(_hashmap);
}

// Returns a boolean value if a key has been put into
// the hashmap
//  - Returns a '1' if a key exists already
//  - Returns a '0' if the key does not exist
//  - Returns a '-9999' if the hashmap is NULL
// The algorithm is:
//  - Call the _hashmap's hash function on the key
//  - Search that bucket to see if the key exists.
// This function should run in average-case constant time
int hashmap_hasKey(hashmap_t* _hashmap, char* key) {
	
	//if hashmap is empty;
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
// The algorithm is:
//  - If a key already exists, do not add it--return
//  - Call the _hashmap's hash function on the key
//  - Store the key/value pair at the end of the buckets chain
//      - You should malloc the key/value in this function
// This function should run in average-case constant time
void hashmap_insert(hashmap_t* _hashmap,char* key,char* value) {
	
	//check if the hashmap is NULL
	if(_hashmap == NULL){
		return;
	}
	
	//create new key/value pair;
	pair_t* newpair = (pair_t*)malloc(sizeof(pair_t));
	newpair->key = (char*)malloc(strlen(key)*sizeof(char)+1);
	newpair->value = (char*)malloc(strlen(value)*sizeof(char)+1);

	//copy string from key to newpair->key;
	//copy string from value to newpair->value; 
	strcpy(newpair->key, key);
	strcpy(newpair->value, value);
	
	//create a new node;
	node_t* newnode = (node_t*)malloc(sizeof(node_t));
	newnode->kv = newpair;
	newnode->next = NULL;

	//get the number of bucket in array;
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
	
	//make an iterator as head of linked list
	node_t* iter = _hashmap->arrayOfLists[bucket];

	//iterator will be newnode if it is empty;
	//else find the end of link list and add the newnode;
	if(iter == NULL){
		_hashmap->arrayOfLists[bucket] = newnode;
		return;
	}
	
	while(iter->next != NULL){
		iter = iter->next;
	}
	iter->next = newnode;
}


// Return a value from a key 
// Returns NULL if the _hashmap is NULL
// Returns NULL if the key is not found
// The algorithm is:
//  - If the key does not exist, then--return NULL if not found.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and return the value
// This function should run in average-case constant time
char* hashmap_getValue(hashmap_t* _hashmap, char* key) {
	
	if(_hashmap == NULL){
		return NULL;
	}
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);		
	node_t* iter = _hashmap->arrayOfLists[bucket];
	while(iter != NULL){	
		if(strcmp(iter->kv->key,key) == 0){
			return iter->kv->value;
		}
		iter = iter->next;
	}
	return NULL;
}

// Remove a key from a hashmap
// The algorithm is:
//  - Determine if the key exists--return if it does not.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and then remove it
// This function should run in average-case constant time
void hashmap_removeKey(hashmap_t* _hashmap, char* key) {
	
	if(_hashmap == NULL){
		return;
	}
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);		
	node_t* iter = _hashmap->arrayOfLists[bucket];
	if(iter == NULL){
		return;
	}
	if(strcmp (iter->kv->key, key) == 0 && iter->next == NULL){
		_hashmap->arrayOfLists[bucket] = NULL;
		free_node(iter);
		return;
	}
	
	node_t* temp = NULL;
	while(iter != NULL){
		if(strcmp (iter->kv->key, key) == 0 && temp != NULL){
			temp->next = iter->next;
			free_node(iter);
			return;
		}
		if(strcmp(iter->kv->key, key) == 0 && temp == NULL){
			_hashmap->arrayOfLists[bucket] = iter->next;
			free_node(iter);
			return;
		}
		temp = iter;
		iter = iter->next;
		
	}
}	

// Update a key with a new Value
// The algorithm is:
//  - Returns immediately if the key does not exist
//  - Call the _hashmap's hash function on the key
//  - Updates the value of the key to the new value
// This function should run in average-case constant time
void hashmap_update(hashmap_t* _hashmap, char* key, char* newValue) {
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
			char* updatedValue = (char*)malloc(strlen(newValue)*sizeof(char)+1);
			strcpy(updatedValue, newValue);
			free(iter->kv->value);
			iter->kv->value = updatedValue;
			
			return;
          	}	
		iter = iter->next;
	}
}


// Prints all of the keys in a hashmap
// The algorithm is:
//  - Iterate through every bucket and print out the keys
// This function should run in O(n) time
void hashmap_printKeys(hashmap_t* _hashmap){
	if(_hashmap == NULL){
		return;
	}
	int i;
	for(i = 0; i < _hashmap->buckets; i++){
		printf("Bucket# %d\n", i);
		node_t* iter = _hashmap->arrayOfLists[i];
		while(iter != NULL){
			printf("Key:%s, Value:%s\n", iter->kv->key, iter->kv->value);
			iter = iter->next;
		}
	}
	return;
}

#endif
