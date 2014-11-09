#include "interface.h"
void input(char *argv)
{
	int i,j,n,count;
	FILE *f = fopen(argv, "r");
	fscanf(f,"%d",&dimension);
	
	x=(int **)malloc(dimension * sizeof(int *));
	for(i=0; i<dimension; i++)
		x[i]=(int *)malloc(dimension * sizeof(int));
	
	for(i=0;i<dimension;i++)
	{
		for(j=0;j<dimension;j++)
		{
			n=fscanf(f,"%d",&x[i][j]);
			//printf("%d ",x[i][j]);
			if(n==EOF)
			{
				break;			
			}
			count=count+1;
		}
		//printf("\n");
		if(n==EOF)
		{
			break;			
		}
	}
	//if(count!=(dimension*dimension)||dimension<=1)
	//printf("Error in Input");
	fclose(f);
}
