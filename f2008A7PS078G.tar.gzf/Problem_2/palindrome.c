#include "header.h"
extern int palindrome(int num)
{
	int t,count=0,i,j;	//t-> variable for holding temporary values, i,j loop variables, 
				//count holds the total digits in the number
	t=num;
	while(t>0)		//loop to find the number of digits in the integer		
	{
		t=t/10;
		count++;	
	}
	int a[count];		//Declare an array to store individual digits which is used for further computation
	t=num;
	for(i=0;i<count;i++)	//segregating each digit of num into the array a[]
	{
		a[i]=t%10;
		t=t/10;
	}
	j=count-1;
	for(i=0;i<count/2;i++)	//checking for palindrome i.e. comparing first digit and last digit, 
	{			//2nd digit and 2nd last digit,so on untill the middle element is reached
		if(a[i]==a[j])
		{
			j=j-1;
			continue;
		}
		else
		{
			return 0;//exception Case-> if any of the a[i]!=a[j] then the function ends returning 0
		}
	}
	return 1;		//Default -> if any exception case is not found	then the number is a palindrome 
}
