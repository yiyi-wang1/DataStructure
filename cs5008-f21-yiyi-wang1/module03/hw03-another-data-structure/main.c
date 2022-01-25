// Compile this assignment with: gcc -g -Wall main.c -o main
// Use this file to implement testing for your
// doubly linked list implementation
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_dll.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.



// ====================================================
// ================== Program Entry ===================
// ====================================================



//Test adding and deleting item from front
void unitTest1(){
	printf("=======Test1========\n");
	dll_t * dll = create_dll();
    	
	dll_push_back(dll, 1);
	dll_push_back(dll, 2);
	dll_push_back(dll, 3);
	dll_push_back(dll, 4);
	dll_remove(dll,2);
	printf("Attempting to add %d\n", 1);
	printf("head: %d, tail: %d\n", dll ->head->data, dll->tail->data);
	printf("Removing: %d\n",dll_pop_front(dll));
	printf("Item in list: %d, %d, %d\n",
		dll_get(dll,0), dll_get(dll,1), dll_get(dll,2));


	free_dll(dll);

}

//Test adding item from the front but deleting from back
void unitTest2(){
	
	printf("=======Test2========\n");
	dll_t * dll = create_dll();
    	
    	
	dll_push_front(dll, 1);
	printf("Attempting to add %d\n", 1);
	printf("head: %d, tail: %d\n", dll ->head->data, dll->tail->data);
	printf("Removing: %d\n",dll_pop_back(dll));

	free_dll(dll);

}

//Test adding item and deleting item from back
void unitTest3(){
	
	printf("=======Test3========\n");
	dll_t * dll = create_dll();
    	
    	
	dll_push_back(dll, 1);
	printf("Attempting to add %d\n", 1);
	printf("Removing: %d\n",dll_pop_back(dll));
	
	free_dll(dll);

}

//Test adding item from back but deleting from front
void unitTest4(){
	
	printf("=======Test4========\n");
	dll_t * dll = create_dll();
    	
    	
	dll_push_back(dll, 1);
	printf("Attempting to add %d\n", 1);
	printf("Removing: %d\n",dll_pop_front(dll));
	
	free_dll(dll);

}

//Test adding from the front and deleting from front
void unitTest10(){
	
	printf("=======Test10========\n");
	dll_t * dll = create_dll();
    	
    	
	dll_push_front(dll, 1);
	printf("Attempting to add %d\n", 1);
	printf("Removing: %d\n",dll_pop_front(dll));
	
	free_dll(dll);

}

//Test reading item (position start from 0)
void unitTest5(){
	printf("=======Test5========\n");
	dll_t * dll = create_dll();
    	
	dll_push_front(dll, 1);
	printf("Attempting to add %d\n", 1);

	dll_push_back(dll,2);
	printf("Attempting to add %d\n", 2);
	
	printf("The first item is: %d, the second item is %d\n",
		dll_get(dll,0), dll_get(dll,1));

	free_dll(dll);

}


//Test reading item from empty list
void unitTest6(){
	printf("=======Test6========\n");
	dll_t * dll = create_dll();
    	
	dll_push_front(dll, 1);
	printf("Attempting to add %d\n", 1);
	printf("Removing: %d\n",dll_pop_front(dll));
	printf("The first item is %d\n", dll_get(dll,0));
	free_dll(dll);

}

//Test reading item when position is larger than list size
void unitTest7(){
	printf("=======Test7========\n");
	dll_t * dll = create_dll();
    	
	dll_push_front(dll, 1);
	printf("Attempting to add %d\n", 1);
	dll_push_back(dll,2);
	printf("Attempting to add %d\n", 2);

	printf("The first item is: %d, the second item is %d, the third item is: %d\n",
		dll_get(dll,0), dll_get(dll,1), dll_get(dll,2));
	free_dll(dll);

}

//Test insert item at given position
void unitTest8(){
	printf("=======Test8========\n");
	dll_t * dll = create_dll();
    	
	dll_push_front(dll, 1);
	printf("Attempting to add %d\n", 1);
	dll_push_back(dll,2);
	printf("Attempting to add %d\n", 2);
	dll_insert(dll, 0, 100);
	printf("Attempting to add %d at position %d\n", 100, 0);
	printf("The size of list is: %d\n", dll->count);
	printf("Item in list: %d, %d, %d\n",
		dll_get(dll,0), dll_get(dll,1), dll_get(dll,2));
	dll_insert(dll, 2 , 101);
	printf("Attempting to add %d at position %d\n", 101, 2);
	printf("The size of list is: %d\n", dll->count);
	printf("Item in list: %d, %d, %d, %d\n",
		dll_get(dll,0), dll_get(dll,1), dll_get(dll,2), dll_get(dll,3));
	dll_insert(dll, 2, 102);
	printf("Attempting to add %d at position %d\n", 102, 2);
	printf("The size of list is %d\n", dll->count);
	printf("Item in list: %d, %d, %d, %d, %d\n",
		dll_get(dll,0), dll_get(dll,1), dll_get(dll,2), dll_get(dll,3), dll_get(dll,4));

	free_dll(dll);

}

//Test remove item at given position
void unitTest9(){
	printf("=======Test9========\n");
	dll_t * dll = create_dll();
    	
	dll_push_front(dll, 1);
	printf("Attempting to add %d\n", 1);
	dll_push_back(dll,2);
	printf("Attempting to add %d\n", 2);
	dll_push_back(dll,3);
	printf("Attempting to add %d\n", 3);
	dll_push_back(dll,4);
	printf("Attempting to add %d\n", 4);
	dll_push_back(dll,5);
	printf("Attempting to add %d\n", 5);

	
	printf("Removing item %d at position %d\n",dll_remove(dll, 0), 0);
	printf("The size of list is: %d\n", dll->count);
	printf("Item in list: %d, %d, %d, %d\n",
		dll_get(dll,0), dll_get(dll,1), dll_get(dll,2),dll_get(dll,3));
	
	printf("Removing item %d at position %d\n",dll_remove(dll, 3), 3);
	printf("The size of list is: %d\n", dll->count);
	printf("Item in list: %d, %d, %d\n",
		dll_get(dll,0), dll_get(dll,1), dll_get(dll,2));
	
	printf("Removing item %d at position %d\n",dll_remove(dll, 1), 1);
	printf("The size of list is: %d\n", dll->count);
	printf("Item in list: %d, %d\n",
		dll_get(dll,0), dll_get(dll,1));
	
	free_dll(dll);

}


int main(){

  	//List of Unit Tests
  	//unitTest1();
	unitTest2();
	unitTest3();
	unitTest4();
	unitTest5();
	unitTest6();	    
   	unitTest7();
	unitTest8();
 	unitTest9();

	unitTest10();
return 0;
}
