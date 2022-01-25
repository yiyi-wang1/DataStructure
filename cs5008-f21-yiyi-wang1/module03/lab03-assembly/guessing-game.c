// Add your program here!
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int guess(int answer){
	int guessNum = 0;
	int n = 0;

	while (guessNum != answer){
	printf("Make a guess:");
	scanf("%d", &guessNum);
	n++;
	if (guessNum > 50 || guessNum == 0){
		printf("Error: please pick a number from 1 to 50.\n");
		}
	else if (guessNum < answer) {
		    printf("No, guess higher!\n");}
	else if (guessNum > answer){
		    printf("No, guess lower!\n");}
	else if (guessNum == answer){
		    printf("You got it!\n");}}
	return n; 
}

int main(){

//the number of attempts for each game
int attempt[5];

attempt[0] = 0;
attempt[1] = 0;
attempt[2] = 0;
attempt[3] = 0;
attempt[4] = 0;

int i;

for (i = 0; i < 5; i++){
	printf("======================================\n");
	printf("CPU Says: picked a number from 1 to 50\n");
	printf("======================================\n");
	srand(time(0));	
	int answer = (rand() % (50 - 1 + 1)) + 1;
	 attempt[i] = guess(answer);}
printf("================================================\n");
printf("Here are the results of your guessing abilities!\n");
printf("================================================\n");
int r;
for (r = 0; r < 5; r++){
	printf("Game %d you took you %d guesses\n", r, attempt[r]);
}
}
