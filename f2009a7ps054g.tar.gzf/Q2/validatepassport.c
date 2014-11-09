#include<stdio.h>

extern int validatepassport(int *date,int *pdate)
{
	if(pdate[2] > date[2])
		return 1;
	else if(pdate[2] < date[2])
		return 0;
	else
	{
		if(pdate[1] > date[1])
			return 1;
		else if(pdate[1] < date[1])
			return 0;
		else
		{
			if(pdate[0] >= date[0])
				return 1;
			else
				return 0;
		}
	}
}
