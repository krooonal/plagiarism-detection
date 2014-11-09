#include<stdio.h>

extern int validatevisa(int *vdate,int *date)
{
	if(vdate[2] > date[2])
		return 1;
	else if(vdate[2] < date[2])
		return 0;
	else
	{
		if(vdate[1] > date[1])
			return 1;
		else if(vdate[1] < date[1])
			return 0;
		else
		{
			if(vdate[0] >= date[0])
				return 1;
			else
				return 0;
		}
	}
}
