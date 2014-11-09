#include"headerfile.h"

void main(){
	int a = getData();
	int row = a;
	
	pid_t pid = 0;
	int status = 0;
	
		
			if(!fork()){
				saveMJ(0, 0, row, row);
			}
			else{
				while(wait(&status)!=-1);
				if(status!=256){
					printf("\nMJ was not saved \n");
				}
			}
}
