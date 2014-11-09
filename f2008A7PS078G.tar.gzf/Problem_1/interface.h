#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
int dimension;
extern int fonk(int i, int j,int p);
int **x;
int k,ret,retz,rety;
void input(char *argv);
extern int fonk2(int i, int j);
extern int fonk3(int i, int j);

