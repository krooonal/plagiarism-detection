#include "interface.h"
int main(int argc, char *argv[])
{
	int retn;
	input(argv[1]);
	int p;
	p=getpid();
	retn =fonk(0,0,p);	
	if(retn!=1)
	{
		printf("\nMarry Jane Not Found\n");	
	}
	printf("\n");
	return 0;
}
