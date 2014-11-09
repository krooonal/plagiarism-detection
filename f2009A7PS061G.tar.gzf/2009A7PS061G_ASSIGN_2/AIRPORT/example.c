

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<math.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include"processFunctions.h"
#include"baggageCounter.h"
#include"immigration.h"
#include"securityCheck.h"
#include"waitingLounge.h"
#include"boarding.h"
#include"parentchild.h"


void main(){
		FILE *input = fopen("input.txt", "r");
		printf("-----------------------READING INPUT---------------------\n");
		int noOfPassengers = getNoOfPassengers(input);
		struct allInfo **passengerPointer = readFile(input, noOfPassengers);
		int pid = fork();
		if(pid==0){
				airport(passengerPointer, noOfPassengers);
				exit(0);
			}
			while(wait(NULL)!=-1);
				
		
	}
