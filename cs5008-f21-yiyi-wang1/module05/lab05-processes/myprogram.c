#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	
	pid_t child1;
	pid_t child2;
	pid_t child3;

	child1 = fork();

	char* myargv[10];
	myargv[0] = "/bin/ls";
	myargv[1] = "ls";
	myargv[2] = "/bin/echo";
	myargv[3] = "echo";
	myargv[4] = "/bin/nl";
	myargv[5] = "testing";
	myargv[6] = "nl";
	myargv[7] = "example1.c";
	myargv[8] = NULL;

	if(child1 == 0){
	
		//This is the first child process
		//it will run the ls command;	
		execl(myargv[0],myargv[1],NULL);
	}else{
		wait(NULL);

		child2 = fork();
		if(child2 == 0){
		
			//This is the second child process
			//it will run the echo command;
			execl(myargv[2],myargv[3],myargv[5],NULL);
		}else{
			wait(NULL);
			child3 = fork();
			if(child3 == 0){

				//This is the third child process
				//it will run the nl command;
				execl(myargv[4],myargv[6],myargv[7],NULL);
			}else{
				wait(NULL);
			}
		}

	}	
	return 0;
}
