#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
//global declerations
int **matrix;
int rowSearch[100];
int columnSearch[100];
int rowIndex = 0;
int columnIndex = 0;
int array[2];
int flag = 0;

//function to get data from the user return a pointer to values of row and column
int  getData(){
	int row = 0;
	int column = 0;
	int i = 0, j = 0;
	FILE *input = NULL;
	input = fopen("input.txt", "r");
	fscanf(input, "%d",&row);
	
	column = row;
	
	matrix = (int **)malloc(sizeof(int *)*row);
	for(i = 0;i<row;i++){
			matrix[i] = (int *)malloc(sizeof(int)*row);
		} 
		
	for(i = 0; i<row; i++){
		for(j = 0; j<column; j++){
			fscanf(input, "%d",&matrix[i][j]);
			
		}
	}
	fclose(input);
	
	
	return row;
}

//function to save MJ
int saveMJ(int i, int j, int row, int column){
	int ret = 0;
	int status = 0;
	pid_t pid = 0;
	
	if(matrix[i][j]==2){	//if input matrix value is 2 then MJ has been saved so this one of the base cases for recursion
		flag = 1;
		rowSearch[rowIndex++]=i;
		columnSearch[columnIndex++]=j;
		//print the relavent data 
		printf("Path is \n");
		int i = 0;
		for(i = rowIndex-1; i>0;i--){
			printf("(%d, %d)-> ", rowSearch[i], columnSearch[i]);
		}
		printf("(0, 0)");
		printf("\nMJ successfully rescued\n");	
		
		ret = 1;		//exit the child with status of 1 to let the parent know that MJ has been saved
		exit(ret);
				
	}
	else if(matrix[i][j]==0){	//if input matrix is 0 that means that MJ has not yet been found and that further children need to be
								//created to look, hence this is the recursion case that creates 1 or 2 children
		rowSearch[rowIndex++] = i;
		columnSearch[columnIndex++] = j;
		
		if(i<row-1 && j<column-1){	//if next row and column are free create two children
			
			pid = fork();		//first child
			if(pid==0){
				saveMJ(i+1, j, row, column);
				
			}
			
			if(pid>0){
					pid = fork();	//second child
					
					if(pid==0){
						saveMJ(i, j+1, row,  column);
						
					}
				}
			while(wait(&status)!=-1);	//return 1 parent if anyone of the child gives one to pass the message that MJ has been saved
			if(status==256){			//else return 0 to tell parent MJ was not found by any member of its subtree
					ret = 1;
				}
			
				exit(ret);
			
			
		}
		else if(j<column-1){	//if only column available create only one child
			pid = fork();
			
			if(pid==0){
				saveMJ(i, j+1, row, column);
			}
			while(wait(&status)!=-1);
			if(status==256){			//return 1 parent if anyone of the child gives one to pass the message that MJ has been saved
					ret = 1;			//else return 0 to tell parent MJ was not found by any member of its subtree
				}
					
				exit(ret);
			
			
		}
		else if(i<row-1){		//if only column available create only one child
			pid = fork();
			
			if(pid==0){
				saveMJ(i+1, j, row, column);
			
			}
			while(wait(&status)!=-1);			
			if(status==256){			//return 1 parent if anyone of the child gives one to pass the message that MJ has been saved
					ret = 1;			//else return 0 to tell parent MJ was not found by any member of its subtree
				}
				
				exit(ret);
		}
	else if(matrix[i][j]==1){	//if input matrix is 1 that means the search for MJ must end hence return 0 to parent saying that 
								//MJ could not be rescued, this is also one of the base cases of recursion
		exit(0);
	}
	}
	
}
