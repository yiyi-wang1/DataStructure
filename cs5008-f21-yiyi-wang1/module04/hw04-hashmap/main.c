// Use this file to write tests. We have started this process for you but
// there is much more than you can and should do. Writing simple tests
// and slowly making them more and more complicated as you develop
// your library is recommended.

#include <stdio.h>
#include "my_hashmap.h"


void unitTest1(){
    // Create our hashmap
    hashmap_t* myHashmap = hashmap_create(5); 
    // Insert a first key/value pair
    hashmap_insert(myHashmap,"pig", "a farm animal");
    // Does hashmap contain key?
    printf("pig was added should be 1: %d\n", hashmap_hasKey(myHashmap, "pig"));
    // Print out the keys
    hashmap_printKeys(myHashmap);
    // Retrieve pig's value 
    printf("pig's value is %s\n", hashmap_getValue(myHashmap, "pig"));
    hashmap_update(myHashmap,"pig","a really cool farm animal");    
    printf("pig's value is updated to: %s\n", hashmap_getValue(myHashmap, "pig"));
    // Remove a key
    hashmap_removeKey(myHashmap,"pig");
    // Does hashmap contain key?
    printf("pig was removed should be 0: %d\n", hashmap_hasKey(myHashmap, "pig"));
    // Finally terminate our hashmap
    hashmap_delete(myHashmap);
}

void  unitTest2(){
    // Create our hashmap
    hashmap_t* myHashmap = hashmap_create(5); 
    // Insert a first key/value pair
    hashmap_insert(myHashmap,"pig", "a farm animal");
    hashmap_insert(myHashmap,"bat", "a farm creature");
    hashmap_insert(myHashmap,"cat", "a funny farm animal");
    hashmap_insert(myHashmap,"dog", "a fun farm animal");
    hashmap_insert(myHashmap,"bear", "a wild farm animal");
    hashmap_insert(myHashmap,"ox", "another farm animal");
    hashmap_insert(myHashmap,"cow", "a favorite farm animal");
    hashmap_insert(myHashmap,"hippo", "a farm animal?");
    hashmap_insert(myHashmap,"elephant", "not a farm animal");
    hashmap_insert(myHashmap,"human", "an animal that farms");
    // Print the keys
    hashmap_printKeys(myHashmap);
   
    printf("-----Test getValue-------\n"); 
    printf("The value is: %s\n",hashmap_getValue(myHashmap, "pig"));
    printf("The value is: %s\n",hashmap_getValue(myHashmap, "bat"));
    printf("The value is: %s\n",hashmap_getValue(myHashmap, "cat"));
    printf("The value is: %s\n",hashmap_getValue(myHashmap, "dog"));
    printf("The value is: %s\n",hashmap_getValue(myHashmap, "bear"));
    printf("The value is: %s\n",hashmap_getValue(myHashmap, "ox"));
    printf("The value is: %s\n",hashmap_getValue(myHashmap, "cow"));
    printf("The value is: %s\n",hashmap_getValue(myHashmap, "hippo"));
    printf("The value is: %s\n",hashmap_getValue(myHashmap, "elephant"));
    printf("The value is: %s\n",hashmap_getValue(myHashmap, "human"));
    printf("The value is: %s\n",hashmap_getValue(myHashmap, "vat"));
    printf("The value is: %s\n",hashmap_getValue(myHashmap, "test"));






 
   printf("-----Test removing-------\n"); 
    hashmap_removeKey(myHashmap,"pig");
    // Does hashmap contain key?
    printf("pig was removed should be 0: %d\n", hashmap_hasKey(myHashmap, "pig"));
    
    hashmap_removeKey(myHashmap,"cat");
    // Does hashmap contain key?
    printf("cat was removed should be 0: %d\n", hashmap_hasKey(myHashmap, "cat"));
    
    hashmap_removeKey(myHashmap,"cow");
    // Does hashmap contain key?
    printf("cow was removed should be 0: %d\n", hashmap_hasKey(myHashmap, "cow"));
    
     hashmap_removeKey(myHashmap,"human");
    // Does hashmap contain key?
    printf("human was removed should be 0: %d\n", hashmap_hasKey(myHashmap, "human"));
    
    hashmap_printKeys(myHashmap);

	
    printf("-----Test updating-------\n");

    hashmap_update(myHashmap,"pig","a");    
    printf("pig's value is updated to: %s\n", hashmap_getValue(myHashmap, "pig"));
    
    hashmap_update(myHashmap,"bat","b");    
    printf("bat's value is updated to: %s\n", hashmap_getValue(myHashmap, "bat"));
     
    hashmap_update(myHashmap,"ox","test ");    
    printf("ox's value is updated to: %s\n", hashmap_getValue(myHashmap, "ox"));
     
    hashmap_update(myHashmap,"man","a really cool farm animal");    
    printf("man's value is updated to: %s\n", hashmap_getValue(myHashmap, "man"));
 
    hashmap_printKeys(myHashmap);

    //finally terminate our hashmap
    hashmap_delete(myHashmap);
}
int main(){

    printf("============ unitTest1() ================\n");
    unitTest1();
    printf("============ unitTest2() ================\n");
    unitTest2();
    
    return 0;
}
