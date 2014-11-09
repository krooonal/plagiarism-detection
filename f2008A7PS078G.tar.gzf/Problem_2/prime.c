#include "header.h"

extern int prime(int num)
{
	int sqr_rt,i;
	if(num%2==0||num%3==0)  		//If the number is divisible by 2,3 it is rejected straight   
									//away reducing further computations
		return 0;
	else
	{
		sqr_rt=sqrt(num);
		for(i=4;i<sqr_rt;i++)	 //Starting from 4 till the square root of the function we find  
		{						//whether the given number is divisible
			if(num%i==0)
			{
				return 0;	
			}
		}	
	}
	return 1;
}
