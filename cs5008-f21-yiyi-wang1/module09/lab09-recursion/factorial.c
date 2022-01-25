// gcc -Wall factorial.c -o factorial
// ./factorial

#include <stdio.h>

unsigned long int factorial(unsigned long int n){
  // TODO: Implement iterative solution here
  unsigned long int i;
  unsigned long int result = 1;
  for(i = 1; i<= n; i++){
	result = i* result;
  }
  return result;
}

unsigned long int factorial_rec(unsigned long int n){
  // TODO: Implement recursive solution here
  if(n <= 1){
	return 1;
  }else{
	return n * factorial_rec(n-1);
  }
}

int main(){

  // Both of these should print the same result!
  printf("factorial(10) = %lu\n",factorial(10));
  printf("factorial_rec(10) = %lu\n",factorial_rec(10));


  return 0;
}
