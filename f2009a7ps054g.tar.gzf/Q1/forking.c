#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>

void main()
{	
	int n;
	int i,j;
	int **a;
	int *p1st, *p2st;
	
	p1st = (int *)malloc(sizeof(int));
	p2st = (int *)malloc(sizeof(int));
	pid_t pid1;
	pid_t pid2;
	
	FILE *input_file,*out_file;
	
	input_file = fopen("input.txt","r");
	fscanf(input_file,"%d",&n);
	
	a = (int **)malloc(n*sizeof(int *));
	for(i =0; i<n; i++)
		*(a+i) = (int *)malloc(n*sizeof(int));
	
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			fscanf(input_file,"%d",*(a+i)+j);
		}
	}
	
	fclose(input_file);
	
	
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			if(*(*(a+i) + j) == 2)
			{
				if(i<n && j<n)
				{
					out_file = fopen("output.txt","w");
					fprintf(out_file,"(%d,%d)",i,j);
					fclose(out_file);
					printf("(%d,%d)",i,j);
				}
				exit(0);
			}
			else if(*(*(a+i) + j) == 0)
			{
				pid1 = fork();
				if(pid1 == 0)
				{
					continue;
				}
				else
				{
					pid2 = fork();
					if(pid2 == 0)
					{
						i++;
						j--;
						continue;
					}
					else
					{
						waitpid(pid1,p1st,0);
						waitpid(pid2,p2st,0);
						if(*p1st == 0 || *p2st == 0)
						{
							if(i<n && j<n)
							{
								out_file = fopen("output.txt","a");
								fprintf(out_file,"-->(%d,%d)",i,j);
								fclose(out_file);
								printf("-->(%d,%d)",i,j);
							}
						}
						else
						{
							if(i==0 && j==0)
							{
								out_file = fopen("output.txt","w");
								fprintf(out_file,"There is no path\n");
								fclose(out_file);
								printf("\nThere is no path\n");
							}
							exit(1);
						}
						
						exit(0);
						
						
					}
				}
			}
			else
				exit(1);
		}
	}
	
		
}	

