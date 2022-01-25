// Add your program here!
#include <stdio.h>

double power(double base, double n){
	double result = base;
	for (int i = 1; i <= n - 1 ; i++){
	result  = result * base;	
	}
	return result;
}

int main(){
	for(double  i = 1; i < 11; i ++){
	double result = power (2, i);
	printf("%f\n", result);
}
}

