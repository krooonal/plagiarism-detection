
#include"functions.h"
//this file include all data structures and functions to access data from file and build the whole data structure

//----------------------------------------GLOBAL DECLERATIONS---------------------------------------




//-----------------------------DATA STRUCTURES----------------------------------------------------


//TIME DATA STRUCTURE
	struct time{
		int hour;
		int minute;
	};
	
//DATE DATA STRUCTURE	
	struct date{
		int day;
		int month;
		int year;
	};
	
	
//THIS DATA STRUCTURE CONTAINS THE INFORMATION RELATING TO THE TICKET AND FLIGHT OF PASSENGER
	struct ticketInfo{
		char ticketNo[10];
		char flightNo[10];
		struct time flightTime;
		struct date flightDate;
		char place[15];
	};



//THIS DATA STRUCTURE CONTAINS THE INFORMATION RELATING TO VISA AND PASSPORT OF PASSENGER	
	struct legalInfo{
	char passportNo[10];
	struct date passportExpiryDate;
	char nationality[15];
	struct date visaExpiryDate;
	char visaFor[10];
	};
	
	
//THIS DATA STRUCTURE CONTAINS THE INFORMATION REALTING TO THE NAME, GENDER AND AGE OF PASSENGER	
	struct personalInfo{
	char firstName[15];
	char lastName[15];
	char gender;
	int age;
	
	};


	
//THIS DATA STRUCTURE CONTAINS THE INFORMATION RELATING ONE BAG OF PASSENGER
	struct bag{
		int weight;
		int contents[10];
		struct bag *next;
	};
	
	
	
//THIS DATA STRUCTURE CONTAINS ALL THE INFORMATION OF A PASSENGER
	struct allInfo{
		struct time entryTime;
		struct date entryDate;
		struct ticketInfo forwardFlight;
		struct ticketInfo returnFlight;
		struct legalInfo legal;
		struct personalInfo personal;
		struct bag **bagInfo;
		int noOfBags;
		int flag;
		int isValid;
	
	};
	
	
	
	//------------------------FUNCTIONS-------------------------------------------------
	
	
	//FUNCTION TO READ TIME FIELD, TAKES INPUT AS FILE POINTER AND TIME STRUCTURE WHERE I/P TIME IS TO BE STORED
	void readTime(FILE * input, struct time *timeVar){
			fscanf(input, "%d", &(timeVar->hour));
			fseek(input, 1, 1);
			fscanf(input, "%d", &(timeVar->minute));
		}
		
	//FUNCTION TO READ DATE FIELD, TAKES INPUT AS FILE POINTER AND DATE STRUCTURE WHERE I/P TIME IS TO BE STORED	
	void readDate(FILE *input, struct date *dateVar){
			fscanf(input, "%d", &(dateVar->day));
			fseek(input, 1, 1);
			fscanf(input, "%d", &(dateVar->month));
			fseek(input, 1, 1);
			fscanf(input, "%d", &(dateVar->year));
		}
		
		
		
	//FUNCTION TO READ FIELDS OF FLIGHTINFO DATA STRUCTURE, I/P FILE POINTER AND FLIGHTINFO DATA STRUCTURE POINTER	
	void readFlightInfo(FILE *input, struct ticketInfo *head){
			fscanf(input,"%s",head->ticketNo);
			fscanf(input,"%s",head->flightNo);
			readTime(input, &(head->flightTime));
			readDate(input, &(head->flightDate));
			fscanf(input, "%s", head->place);
			
			
		}
		
	//FUNCTION TO READ FIELDS OF LEGALINFO DATA STRUCTURE, I/P FILE POINTER AND LEGALINFO DATA STRUCTURE POINTER
	void readLegalInfo(FILE *input, struct legalInfo *head){
			fscanf(input,"%s",head->passportNo);
			readDate(input, &(head->passportExpiryDate));
			fscanf(input, "%s",head->nationality);
			readDate(input, &(head->visaExpiryDate));
			fscanf(input, "%s",head->visaFor);	
		}
		
		
	//FUNCTION TO READ FIELDS OF PERSONALINFO DATA STRUCTURE, I/P FILE POINTER AND PERSONALINFO DATA STRUCTURE POINTER	
	int readPersonalInfo(FILE *input, struct personalInfo *head){
			fscanf(input,"%s",head->firstName);
			fscanf(input, "%s",head->lastName);
			fseek(input, 1, 1);
			fscanf(input, "%c", &(head->gender));
			fscanf(input, "%d", &(head->age));
			}
			
			
	//FUNCTION TO CREATE A BAG DATA STRUCTURE, TKAES IN THE HEADER POINTER TO LINKED LIST AND ADD NEW FEILDS AT THE END
	//OF THE LINKED LIST, ONLY FILLS THE FEILD WEIGHT, CONTENTS OF BAG IS ADDED BY FUNCTION fillBags(FILE *, struct allInfo *)
	void readBagInfo(FILE *input, struct allInfo *head){
			int i = 0;
			struct bag *temp = NULL;
			struct bag *tempInsert = NULL;
			fscanf(input, "%d", &(head->noOfBags));
			head->bagInfo = (struct bag **)malloc(head->noOfBags*sizeof(struct bag *));
			i = 0;
			while(i<head->noOfBags){
					head->bagInfo[i] = (struct bag *)malloc(sizeof(struct bag));
					fscanf(input, "%d", &(head->bagInfo[i]->weight));
					i++;
				}
			
		}
		//FUNCTION THAT ADD THE CONTENTS OF EACH BAG BY INITIALIZING THE CONTENTS ARRAY OF EACH BAG DATA STRUCTURE	
		void addContentsToBag(FILE *input, struct bag *bagPointer){
				int i = 0;
				int temp_var = 0;
				
				while(i<10){
						fscanf(input, "%d",&temp_var);
						bagPointer->contents[i] = temp_var;
						i++;
					}
			}
		//FILLS THE BAGS WITH THE CONTENTS OF EACH BAGS, ACTUAL FILLING DONE BY addContentsToBag(FILE *, struct bag *),
		//THIS FUNCTION ONLY CALLS IT ITERATIVELY 
		void fillBags(FILE *input, struct allInfo *all){
				int i = 0;
				while(i<all->noOfBags){
						addContentsToBag(input, all->bagInfo[i]);
						i++;
					}
				
			}
			
		//FUNCTION THAT CREATES A ALLINFO DATA STRUCTURE
	void readInput(FILE *input, struct allInfo *all){
		
			int flag = 0;
			fscanf(input, "%d", &flag);
			all->flag = flag;
			readTime(input, &(all->entryTime));
			fseek(input, 1, 1);
			readDate(input, &(all->entryDate));
			readFlightInfo(input, &(all->forwardFlight));
			if(flag){
					readFlightInfo(input, &(all->returnFlight));
				}
			readLegalInfo(input, &(all->legal));
			readPersonalInfo(input, &(all->personal));
			readBagInfo(input, all);
			fillBags(input, all);	
			
		}
	//FUNCTION THAT READS THE FILE AND BUILDS THE COMPLETE DATA STRUCTURE
	struct allInfo ** readFile(FILE *input, int noOfPassengers){
			
			int i = 0;
			
			struct allInfo **passengers = (struct allInfo **)malloc(noOfPassengers*sizeof(struct allInfo *));
			while(i<noOfPassengers){
					passengers[i] = (struct allInfo *)malloc(sizeof(struct allInfo));
					readInput(input, passengers[i]);
					i++;
				}
				return passengers;
			
		}
		int getNoOfPassengers(FILE *input){
				int no = 0;
				fscanf(input, "%d", &no);
				return no;
			}
	

	
	
