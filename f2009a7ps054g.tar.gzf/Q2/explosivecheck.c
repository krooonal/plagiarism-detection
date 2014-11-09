#include<stdio.h>

extern int explosivecheck(int num)
{
	int rev,temp;
	temp = num;
	rev = 0;
	
	while(temp>0)
	{
		rev = rev*10 + temp%10;
		temp = temp/10;
	}
	
	if(rev == num)
		return 1;
	else
		return 0;
	
}
