// Use this file to write tests. We have started this process for you but
// there is much more than you can and should do. Writing simple tests
// and slowly making them more and more complicated as you develop
// your library is recommended.

// Compile this assignment with: gcc -g -Wall linked_hashmap_tests.c -o tests
//
// Run with: ./tests
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "linked_hashmap.h"

// write a comment of what you are testing in this function

//Test create and delete hashmap
int unitTest1(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(5);
    hashmap_delete(test);
    passed = 1;
    return passed;

}

//Test has_key for a missing key
int unitTest2(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(10);

    if(hashmap_hasKey(test, "cow") == 0){
	passed = 1;
    }

    hashmap_delete(test);
    return passed;

}


//Test insert key and hasKey
int unitTest3(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(10);
    
    hashmap_insert(test, "pig", "A wild farm animal.");
    if(hashmap_hasKey(test, "pig") == 1){
	passed = 1;
    }

    hashmap_delete(test);
    return passed;

}

//Test insert key with Lexicographical order and hasKey
int unitTest4(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(10);
    
    hashmap_insert(test, "pig", "A wild farm animal."); 
    hashmap_insert(test, "cat", "A funny animal.");

    if(hashmap_hasKey(test, "pig") == 1 && hashmap_hasKey(test, "cat") == 1){
	passed = 1;
    }

    hashmap_delete(test);
    return passed;
}


//Test insert key and remove key
int unitTest5(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(10);
    
    hashmap_insert(test, "pig", "A wild farm animal.");
    hashmap_removeKey(test, "pig");

    if(hashmap_hasKey(test, "pig") == 0){
	passed = 1;
    }

    hashmap_delete(test);
    return passed;

}

//Test insert key with Lexicographical order and remove key
int unitTest6(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(10);
    
    hashmap_insert(test, "pig", "A wild farm animal."); 
    hashmap_insert(test, "cat", "A funny animal.");

    hashmap_removeKey(test, "cat");
    hashmap_removeKey(test, "pig");


    if(hashmap_hasKey(test, "pig") == 0 && hashmap_hasKey(test, "cat") == 0){
	passed = 1;
    }

    hashmap_delete(test);
    return passed;
}
 
//Test insert and remove multiple keys
int unitTest7(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(10);
    
    int i;
    char text[5];
    for(i = 0; i < 100; i++){
	sprintf(text, "%d", i);
	hashmap_insert(test, text, "test value");
	}

    for(i = 0; i < 100; i++){
	sprintf(text, "%d", i);
	hashmap_removeKey(test, text);
	}

    if(test->count == 0){
	passed = 1;
    }

    hashmap_delete(test);
    return passed;

}

//Test insert key with Lexicographical order and remove multiple keys
int unitTest8(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(10);
    
    int i;
    char text[5];
    for(i = 0; i < 100; i++){
	sprintf(text, "%d", i);
	hashmap_insert(test, text, "test value");
	}

    for(i = 0; i < 100; i++){
	sprintf(text, "%d", i);
	hashmap_removeKey(test, text);
	}

    if(test->count == 0){
	passed = 1;
    }
    
    hashmap_delete(test);
    return passed;

}

//Test insert key and update key
int unitTest9(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(10);
    
    hashmap_insert(test, "cow", "A common farm animal.");
    hashmap_insert(test, "pig", "A wild farm animal.");
    hashmap_update(test, "pig", "Updated");


    char* result = hashmap_getValue(test, "pig");
    if(strcmp(result, "Updated") == 0){
	passed = 1;
    }

    hashmap_delete(test);
    free(result);
    return passed;

}

//Test insert key with Lexicographical order and update key
int unitTest10(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(10);
     

    hashmap_insert(test, "cat", "A funny animal.");
    hashmap_insert(test, "pig", "A wild farm animal.");
    hashmap_update(test, "pig", "Updated");
   
    char* result = hashmap_getValue(test, "pig");
 
    if(strcmp(result, "Updated") == 0){
	passed = 1;
    }

    hashmap_delete(test);
    free(result);
    return passed;

}

//Test the insertion order
int unitTest11(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(5);
   
    hashmap_insert(test, "cow", "A common farm animal.");
    hashmap_insert(test, "cat", "A funny animal.");
    hashmap_insert(test, "pig", "A wild farm animal.");
    hashmap_insert(test, "dog", "A friendly animal.");
    hashmap_insert(test, "bat", "A night animal.");
    
    pair_t* firstPair = hashmap_getFirst(test);
    pair_t* lastPair = hashmap_getLast(test);

    if(strcmp(firstPair->key,"cow") == 0 && 
	strcmp(lastPair->key,"bat") == 0){
		passed = 1;
    }

    hashmap_delete(test);
    
    free(firstPair->key);
    free(firstPair->value);
    free(firstPair);
    free(lastPair->key);
    free(lastPair->value);
    free(lastPair);

    return passed;
}
   
//Test the lexicographic order
int unitTest12(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(5);
   
    hashmap_insert(test, "cow", "A common farm animal."); 
    hashmap_insert(test, "cat", "A funny animal.");
    hashmap_insert(test, "pig", "A wild farm animal.");
    hashmap_insert(test, "dog", "A friendly animal.");
    hashmap_insert(test, "bat", "A night animal.");
    
    pair_t* firstPair = hashmap_getFirst(test);
    pair_t* lastPair = hashmap_getLast(test);

 
    if(strcmp(firstPair->key,"bat") == 0 && 
	strcmp(lastPair->key,"pig") == 0){
		passed = 1;
    }
 
    free(firstPair->key);
    free(firstPair->value);
    free(firstPair);
    free(lastPair->key);
    free(lastPair->value);
    free(lastPair);


    hashmap_delete(test);
    return passed;
}

//Test getValue function for exited key
int unitTest13(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(5);
   
    hashmap_insert(test, "cow", "A common farm animal.");
    hashmap_insert(test, "cat", "A funny animal.");
    hashmap_insert(test, "pig", "A wild farm animal.");
    hashmap_insert(test, "dog", "A friendly animal.");
    hashmap_insert(test, "bat", "A night animal.");
 
   char* result = hashmap_getValue(test, "cow");
   if(strcmp(result,"A common farm animal.") == 0){ 
	passed = 1;
   }	
    hashmap_delete(test);
    free(result);
    return passed;
}
 
//Test getValue function for key does not exit
int unitTest14(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(5);
    
    hashmap_insert(test, "cat", "A funny animal.");
    hashmap_insert(test, "pig", "A wild farm animal.");
    hashmap_insert(test, "dog", "A friendly animal.");
    hashmap_insert(test, "bat", "A night animal.");
    
    char* result = hashmap_getValue(test, "human");
    if(result == NULL){
		passed = 1;
    }

    hashmap_delete(test);
    free(result);
    return passed;
}
 
//Test getFirst function for key does not exit
int unitTest15(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(5);
     
    pair_t* result = hashmap_getFirst(test);
    if(result == NULL){
		passed = 1;
    }

    hashmap_delete(test);
 
    return passed;
}
 
//Test getLast function for key does not exit
int unitTest16(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(5);
     
    pair_t* result = hashmap_getLast(test);
    if(result == NULL){
		passed = 1;
    }

    hashmap_delete(test);
 
   
   return passed;
}
 

//Test getFirst function and removeKey function
int unitTest17(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(5);
    
    hashmap_insert(test, "cow", "A common farm animal.");
    hashmap_insert(test, "cat", "A funny animal.");
    hashmap_insert(test, "pig", "A wild farm animal.");
    hashmap_insert(test, "dog", "A friendly animal.");
    hashmap_insert(test, "bat", "A night animal.");
 
    hashmap_removeKey(test, "cow");
    
    pair_t* result = hashmap_getFirst(test);
    
    if(strcmp(result->key,"cat") == 0){ 
	passed = 1;
    }

    hashmap_delete(test);
    free(result->value);
    free(result->key);
    free(result);

    return passed;
}
 
//Test getLast function and removeKey function
int unitTest18(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(5);
    
    hashmap_insert(test, "cow", "A common farm animal.");
    hashmap_insert(test, "cat", "A funny animal.");
    hashmap_insert(test, "pig", "A wild farm animal.");
    hashmap_insert(test, "dog", "A friendly animal.");
    hashmap_insert(test, "bat", "A night animal.");
 
    hashmap_removeKey(test, "bat");
    
    pair_t* result = hashmap_getLast(test);
    
    if(strcmp(result->key,"dog") == 0){ 
	passed = 1;
    }

    hashmap_delete(test);
    free(result->value);
    free(result->key);
    free(result);

    return passed;
}

//Test getFirst function and removeKey function for lexico order
int unitTest19(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(5);
    
    hashmap_insert(test, "cow", "A common farm animal."); 
    hashmap_insert(test, "cat", "A funny animal.");
    hashmap_insert(test, "pig", "A wild farm animal.");
    hashmap_insert(test, "dog", "A friendly animal.");
    hashmap_insert(test, "bat", "A night animal.");
    
    hashmap_removeKey(test, "bat");
    pair_t* result = hashmap_getFirst(test);
    
    if(strcmp(result->key,"cat") == 0){ 
	passed = 1;
    }

    hashmap_delete(test);
    free(result->value);
    free(result->key);
    free(result);

 return passed;
}
 
//Test getLast function and removeKey function for lexico order
int unitTest20(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(5);
    
    hashmap_insert(test, "cow", "A common farm animal."); 
    hashmap_insert(test, "cat", "A funny animal.");
    hashmap_insert(test, "pig", "A wild farm animal.");
    hashmap_insert(test, "dog", "A friendly animal.");
    hashmap_insert(test, "bat", "A night animal.");
 
    hashmap_removeKey(test, "pig");
    pair_t* result = hashmap_getLast(test);
    
    if(strcmp(result->key,"dog") == 0){ 
	passed = 1;
    }

    hashmap_delete(test);
    free(result->key);
    free(result->value);
    free(result);

    return passed;
}


   
int (*unitTests[])(int)={
    unitTest1,
    unitTest2,
    unitTest3,
    //unitTest4,
    unitTest5,
    //unitTest6,
    unitTest7,
    //unitTest8,
    unitTest9,
    //unitTest10,
    unitTest11,
    //unitTest12,
    unitTest13,
    unitTest14,
    unitTest15,
    unitTest16,
    unitTest17,
    unitTest18,
    //unitTest19,
    //unitTest20,
    NULL
};


// ====================================================
// ================== Program Entry ===================
// ====================================================
int main() {
    unsigned int testsPassed = 0;
    // List of Unit Tests to test your data structure
    int counter =0;
    while(unitTests[counter]!=NULL){
	printf("========unitTest %d========\n", counter);
        if(1==unitTests[counter](1)){
		printf("passed test\n");
		testsPassed++;	
	}else{
		printf("failed test, missing functionality, or incorrect test\n");
	}
        counter++;
    }

    printf("%d of %d tests passed\n", testsPassed, counter);

    return 0;
}
