// Implement your cycle count tool here.
//
#include <stdio.h>
#include<string.h>

void printResult (int result, char name[]){
	if (result != 0){
	printf("%s: %d\n", name, result);
	};

}

int main(int argc, char** argv){

//use this function to get the file name.
	int i;
	char fileName[1024];
	
	if(argc <= 1){
		printf("Error. Please run with file name.\n");
	}
	if(argc > 1){
		for(i = 0; i < argc; i++){
		//In order to only open the file we want,
		//we need to store the file name in another string.
		//
			strcpy(fileName, argv[1]);
		}		
	
	//initilize the count of instructions
	int add = 0;
	int sub = 0;
	int mul = 0;
	int div = 0;
	int mov = 0;
	int lea = 0;
	int push = 0;
	int pop = 0;
	int ret = 0;

	FILE* filePointer;
	filePointer = fopen(fileName, "r");
	
	char buffer[1024];
	
	//get each line of file;
	while(fgets(buffer, 1024, filePointer)){
		
		char word[10];
		int count;
		int wordCount = 0;
	
	//the following for loop is getting the first word in each line
	//without whitespace;
	//the reason to get the first word in each line is:
	//when the test program output words, there may be some words contain the instruction word
	//for example: "please" contain "lea" 
	//If we check the whole line from file, the count will not be accurate;
	//
		for(count = 0; buffer[count]; count++){
		  if(buffer[count] != ' '){
			word[wordCount] = buffer[count];
			wordCount++;
		  }
		if(buffer[count] == ' ' && wordCount != 0){
			break;
		  }
		}
		word[wordCount] ='\0';
	
	//When we get the first word in each line, we could check if it is instructor;
	//since the instructor is always the first word in lines;
	//
		if (strstr (word, "add")){
			add++;
		}
		if (strstr (word, "sub")){
			sub++;
		}
		if (strstr (word, "mul")){
			mul++;
		}
		if (strstr (word, "div")){
			div++;
		}
		if (strstr (word, "mov")){
			mov++;
		}
		if (strstr (word, "lea")){
			lea++;
		}
		if (strstr (word, "push")){
			push++;
		}
		if (strstr (word, "pop")){
			pop++;
		}
		if (strstr (word, "ret")){
			ret++;
		}
	}
	
	fclose(filePointer);
	
	printResult(add, "add");
	printResult(sub, "sub");
	printResult(mul, "mul");
	printResult(div, "div");
	printResult(mov, "mov");
	printResult(lea, "lea");
	printResult(push, "push");
	printResult(pop, "pop");
	printResult(ret, "ret");

	int sum = add + sub + mul + div + mov + lea + push + pop + ret;
	int total = add + sub + mul * 3 + div * 24 + mov + lea * 3 + push + pop + ret;
	
	printf("Total instruction is: %d\n", sum);
	printf("Total cycles is: %d\n", total);

}
return 0;

}
