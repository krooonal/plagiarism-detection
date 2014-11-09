#include<stdio.h>

extern int primecheck(int num)
{
	int i;
	
	if(num % 2 == 0)
		return 0;
	else
	{
		i=3;
		while(i<= num/2)
		{
			if(num % i == 0)
				return 0;
			i = i + 2;
		}
		
		return 1;
	}
}
