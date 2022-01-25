#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(){

	int i;
	if(fork() == 0){
		for(i = 1; i <5; i++){
			printf("This is Child.\n");
		}
	}else{
		for(i = 1; i < 5; i++){
			printf("This is parent.\n");
		}
	}

}
