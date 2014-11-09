#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include"inputoutput.h"
//------------------------------GLOBAL VARIABLES-----------------------------------
int seatNo = 1;
int baggageId = 0;

	//FUNCTION USED BY WEIGHT PROCESS RETURNS THE EXTRA AMOUNT TO BE  PAID BY PASSENGER
int weightFunction(struct allInfo *passenger){
		int extraAmount = 0;
		int weight = 0;
		int i = 0;
		struct bag **bagPointer = passenger->bagInfo;
		int extraBags = passenger->noOfBags -3;
		if(extraBags>0){
				extraAmount = extraAmount + extraBags*40;
			}
			while(i<passenger->noOfBags){
					weight = bagPointer[i]->weight - 20;
					if(weight>0){
							extraAmount = extraAmount + weight*2;
						}
						i++;
				}
				if(extraAmount>0){
						printf("WEIGHT-->The Passenger %s is asked to pay %d\n",passenger->forwardFlight.ticketNo, extraAmount);
					}
				return extraAmount;
	}
//FUNCTION USED BY LUGGAGE SECURITY PROCESS, CHECK LUGGAGE AND CLEARS USELESS CONTENTS OF BAGGAGE
void luggageSecurityFunction(struct allInfo *passenger){

		int index = 0;
		int bags = passenger->noOfBags;
		int noToBePrinted[10*(bags-1)];
		int j = 0;
		int i = 0;
		for(i = 0;i<10*(bags-1);i++){
				noToBePrinted[i] = 0;
			}
			i = 0;
		while(i<bags-1){
			
				for(j=0;j<10;j++){
						if(!palindrome(passenger->bagInfo[i]->contents[j]) || colorful(passenger->bagInfo[i]->contents[j])){
							noToBePrinted[index++] = passenger->bagInfo[i]->contents[j];
								passenger->bagInfo[i]->contents[j] = 0;
							}
					}
					i++;
			}
			printf("LUGGAGESECURITY-->Luggage Security has removed following items from passenger %s\n",passenger->forwardFlight.ticketNo);
			for(i = 0; i< index ;i++){
					printf("%d ",noToBePrinted[i]);
				}
				printf("\n");
				
	}
	
	void luggageSecurityAfter(struct allInfo *passenger){
				printf("LUGGAGE SECURITY-->Luggage Security is generating ticketNo %s \n",passenger->forwardFlight.ticketNo);
				FILE *ticketfile = fopen(passenger->forwardFlight.ticketNo, "a");
				fprintf(ticketfile, "baggage id = %d ",baggageId++);
				fclose(ticketfile);
		}
//FUNCTION USED TO CHECK WHETHER THE PASSENGER IS TO BE ALLOWED INTO AIRPORT, CLEARS ISVALID IF PASSENGER IS NOT ALLOWED
int entryCheck(struct allInfo *passenger){
		int multiplier = 0;
		int yearDif = passenger->forwardFlight.flightDate.year - passenger->entryDate.year;
		int monthDif = passenger->forwardFlight.flightDate.month - passenger->entryDate.month;
		int dayDif = passenger->forwardFlight.flightDate.day - passenger->entryDate.day;
		int hourDif = passenger->forwardFlight.flightTime.hour - passenger->entryTime.hour;
		int minDif = passenger->forwardFlight.flightTime.minute - passenger->entryTime.minute;
		monthDif = monthDif + 12 *(yearDif);
		int temp = passenger->forwardFlight.flightDate.month;
		switch(temp){
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12: multiplier = 31;
							break;
				case 4:
				case 6:
				case 9:
				case 11: multiplier = 30;
							break;
				case 2: multiplier = 28;
							break;
			}
			if(multiplier==28 && passenger->forwardFlight.flightDate.year%4==0){
					multiplier++;
				}
		dayDif = dayDif + multiplier*monthDif;
		hourDif = hourDif + 24*dayDif;
		minDif = minDif + 60*hourDif;
		if(minDif>240){
				passenger->isValid = 0;
			}
			return minDif;
	}
//working	
void boardingPassFunction(struct allInfo *passenger, FILE *output){
		printf("BOARDING PASS-->Boarding Pass is generating ticketNo %s \n",passenger->forwardFlight.ticketNo);
		char meal[3][20] = {"vegetarian", "non-vegetarian", "asian-vegetarian"};
		int age = passenger->personal.age;
		char gender = passenger->personal.gender;
		char firstName[10];
		char lastName[10];
		strcpy(firstName, passenger->personal.firstName);
		strcpy(firstName, passenger->personal.lastName);
		int random = rand()%2;
		fprintf(output, "%s ", passenger->forwardFlight.ticketNo);
		fprintf(output, "%d ", passenger->personal.age);
		fprintf(output, "%c ", passenger->personal.gender);
		fprintf(output, "seat no = %d ", seatNo++);
		fprintf(output, "%s ", meal[random]);
		
		
	}
	//working
	int validityCheck(struct date *date1, struct date *date2){
			int multiplier = 0;
			int yearDif = date1->year - date2->year;
			int monthDif = date1->month - date2->month;
			int dayDif = date1->day - date2->day;
			
					monthDif = monthDif + 12 *(yearDif);
		int temp = date1->month;
		switch(temp){
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12: multiplier = 31;
							break;
				case 4:
				case 6:
				case 9:
				case 11: multiplier = 30;
							break;
				case 2: multiplier = 28;
							break;
			}
			if(multiplier==28 && date1->year%4==0){
					multiplier++;
				}
		dayDif = dayDif + multiplier*monthDif;
			return dayDif;
		}
		//working
		int passportCheck(struct allInfo *passenger, FILE *output){
				int dif = validityCheck(&(passenger->legal.passportExpiryDate) , &(passenger->forwardFlight.flightDate));
				if(dif<0){
						fprintf(output, "immigration not cleared ");
						return 0;
					}
					
					return 1;
			}
			
			//working
		int visaCheck(struct allInfo *passenger, FILE *output){
				int dif = 0;
				int cmp = strcmp(passenger->legal.nationality, passenger->forwardFlight.place);
				if(cmp==0){
						dif = validityCheck(&(passenger->legal.visaExpiryDate), &(passenger->forwardFlight.flightDate));
						if(dif<0){
								fprintf(output, "immigration not cleared ");
								return 0;
							} 
							
					}
					else{
							if(passenger->flag==1){
										dif = validityCheck(&(passenger->legal.visaExpiryDate), &(passenger->returnFlight.flightDate));
								}
								else{
										dif = validityCheck(&(passenger->legal.visaExpiryDate), &(passenger->forwardFlight.flightDate));
									}
								if(dif<0){
								fprintf(output, "immigration not cleared ");
								return 0;
							} 
						}
						fprintf(output, "immigration cleared ");
						return 1;
			}
			
			void handBagCheck(struct allInfo *passenger){
				int j = 0;
				int index = 0;
				int notToBeAllowed[10] = {0};
					int i = passenger->noOfBags -1;
					for(j=0;j<10;j++){
						if(!palindrome(passenger->bagInfo[i]->contents[j]) || prime(passenger->bagInfo[i]->contents[j])){
								notToBeAllowed[index++] = passenger->bagInfo[i]->contents[j];
								passenger->bagInfo[i]->contents[j] = 0;
							}
					}
					printf("security has removed the following items from ticketno %s ",passenger->forwardFlight.ticketNo);
					for(i = 0;i<index;i++){
							printf(" %d ",notToBeAllowed[i]);
						}
						printf("\n");
				}
				
				
	int passengerCheck(struct allInfo *passenger){
		char temp[20];
		int flag = 0;
		int i = 0;
		FILE *print = fopen(passenger->forwardFlight.ticketNo, "r");
		fscanf(print, "%s",temp);
		while(i<20){
				if(strcmp(temp, "not") == 0){
					flag = 1;
					break;
					}
					fscanf(print, "%s",temp);
					i++;
			}
			fclose(print);
			if(flag == 1){
					return 0;
				}
				else{
						return 1;
					}
	}
