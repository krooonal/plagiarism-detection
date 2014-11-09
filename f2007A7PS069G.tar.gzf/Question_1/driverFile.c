#include <stdio.h>
int main(){
	int ch,n,i;
	n=matrixDimensionsInput();
	ch = PathCalculation(n);
	
	if(ch!=1){
		printf("Spiderman Couldnt rescue Mary Jane!");
	}
	return 0;
}
