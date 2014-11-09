#include "headerFile.h"
#include<stdio.h>



// Function to input the Size of the Array/Matrix
int matrixDimensionsInput(void){
	int n;
	printf("Enter the Size of the Square Matrix 'N'x'N'\n");
	printf("n=");
	scanf("%d",&n);
	return n;
}

//Function to read the Matrix Values from the keyboard through the terminal and then calculate the possibility of a path
int PathCalculation(int n){
	int matrix[n][n];   //Matrix to store the input values
	int path[2*n-1][2]; // Matrix to store the path from spiderman to Mary Jane or from (0,0) to (n-1,n-1)
	int input,i,j,k,l; // variables i & j are used to index matrix[][] and k,l are used to index path[][]
	int count=0;

//The nested for loops are used to read and store the matrix values
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==0 && j==0){
				printf("(0,0)=%d\n",INITIAL_VALUE);
				matrix[0][0]=INITIAL_VALUE;
				continue;
			}
			if(i==(n-1) && j==(n-1)){
				printf("(%d,%d)=%d\n",n-1,n-1,FINAL_VALUE);
				matrix[n][n]=FINAL_VALUE;
				continue;
			}
// do..while() loop is used to make sure that the matrix values are either 0 or 1
			do{
				printf("(%d,%d)=",i,j);
				scanf("%d",&input);
				matrix[i][j]=input;
				if(input !=0 && input !=1){
					printf("Input values can only be 0 or 1. Please re-enter them.\n");
					continue;
				}
			}while(input != 0 && input !=1);

		}
	}
	i=0;
	j=0;
	k=0;

	fork(); // The main Parent process starts from here

/* The Maze solving Algorithm starts from here. The algorithm is based on "Recursive Bactracking Algorithm" - can be found on wikipedia.com
*/

	while(1){
		if(!fork()){
			if((j+1)<n){
				if(matrix[i][j]==0){
					path[k][0]=i;
					path[k][1]=j;
					j++;
					k++;
					wait(NULL);
					continue;
				}
				else if(matrix[i][j]==2){
					count =1;
					break;
					wait(NULL);
				}
				else{
					j--;
					i++;
					if(!fork()){
						if(matrix[i][j]==0){
							path[k][0]=i;
							path[k][0]=j;
							j++;
							k++;
							continue;
						}
						else if(matrix[i][j]==2){
							count =1;
							path[k][0]=i;
							path[k][0]=j;
							break;
						}
						else{
							break;
						}
					}
				}
			}
			else{
				if(matrix[i][j]==0){
					path[k][0]=i;
					path[k][1]=j;
					i++;
					k++;
					wait(NULL);
					continue;
				}
				else if(matrix[i][j]==2){
					count =1;
					break;
				}
				else{
					break;
				}
			}
		}	
	}
	if(count ==1){
		printf("Spiderman Saves Mary Jane\n");
		printf("The requested path is \n");
		for(i=2*n-1;i>0;i--){
			printf("(%d,%d), ",path[i][0],path[i][1]);
		}
	}
		
	return count;
}

