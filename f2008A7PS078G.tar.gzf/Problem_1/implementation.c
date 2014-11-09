#include "interface.h"
extern int fonk(int i,int j,int p)
{
	int k,ret,rety,retz;
	pid_t y,z;
	
		y=fork();
		if(y==0)
		{	
			if(x[i+1][j]==1)
			{
				exit(0);					
			}
			else if((i+1)==(dimension-1))
			{
				ret=fonk2(i+1,j);//Boundary Case
				if(ret==1)
					exit(1);				
			}
			else
			{		
				ret=fonk(i+1,j,10);
				if(ret==1)
				{
					exit(1);
				}
			}		
		}
		
		z=fork();
		if(z==0)
		{	
			if(x[i][j+1]==1)
			{
				exit(0);					
			}
			else if((j+1)==(dimension-1))
			{
				ret=fonk3(i,j+1);//Boundary Case
				if(ret==1)
				exit(1);		
			}
			else
			{
				fonk(i,j+1,10);
				if(ret==1)
				{
					exit(1);
				}
			}		
		}
	
	waitpid(y,&rety,NULL);
	waitpid(z,&retz,NULL);
	if(rety==256)
	{ 
		printf("->(%d,%d)",i,j);
		if(p==getpid())
		return(1);
		else exit(1);
	}
	else if(retz==256)
	{
		printf("->(%d,%d)",i,j);
		if(p==getpid())
		return(1);
		else exit(1);
	}
	else if(p==getpid())
		return(0);
	else 
		exit(0);
}
extern int fonk2(int i,int j)
{
	int ret,rety;
	pid_t y;
	y=fork();
	if(y==0)
	{
		if(i==(dimension-1)&&j==(dimension-1))
		{
			printf("Mary Jane Found \n");
			exit(1);
		}
		else if((x[i][j]!=0))
			exit(0);
		else if(x[i][j+1]==1)
		{
			exit(0);					
		}
		else
		{
			ret = fonk2(i,j+1);
			if(ret==1)
				exit(1);
			else
				exit(0);
		}
	}
	waitpid(y,&rety,NULL);
	if(rety==256)
	{	if(i==(dimension-1)&&j==(dimension-1))
		printf("(%d,%d)",i,j);
		else
		printf("->(%d,%d)",i,j);
		
		exit(1);
	}
}
extern int fonk3(int i, int j)
{
	int rety, ret;
	pid_t y;
	y=fork();
	if(y==0)
	{
		if(i==(dimension-1)&&j==(dimension-1))
		{
			printf("Mary Jane Found \n");
			exit(1);
		}
		else
		{
			ret=fonk3(i+1,j);
			if(ret==1)
				exit(1);
			else
				exit(0);
		}	
	}
	waitpid(y,&rety,NULL);
	if(rety==256)
	{	
		if(i==(dimension-1)&&j==(dimension-1))
		printf("(%d,%d)",i,j);
		else
		printf("->(%d,%d)",i,j);
		exit(1);
	}
}
