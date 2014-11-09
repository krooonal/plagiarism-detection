#include<stdio.h>
#include<stdlib.h>

extern int getrandom(int num)
{
	//randomize();
	int n;
	n = random();
	return n;
}
