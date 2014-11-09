#include "header.h"
int main(int argc, char *argv[])
{
	int entries,i,flag=0;
	pid_t airp;
	FILE *f = fopen(argv[1], "r");
	fscanf(f,"%d",&entries,f);
	struct flyers **array;
	array=(struct flyers**)malloc(sizeof (struct flyers *));
	for(i=0;i<entries;i++)
	{
		array[i]=(struct flyers*)malloc(sizeof (struct flyers));
		
	}
	input(array,entries,f);
	airp=fork();
	if(airp==0)
		{
			airport(array,entries);
			exit(0);
		}
	while(wait(NULL)!=-1);
	
	return 0;
}
