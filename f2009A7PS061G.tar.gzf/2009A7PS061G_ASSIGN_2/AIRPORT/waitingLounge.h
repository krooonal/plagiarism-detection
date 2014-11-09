
//this file contains processes waiting lounge and its children, cafe and restroom
void restRoom(struct allInfo **main_pointer, int noOfPassengers){
	
	printf("RESTROOM IS UP AND RUNNING \n");
	
	
	int index = 0;
	int i = 0;
	int select = 0;
	FILE *waitingPassengersFile = NULL;			//file created by waiting lounge that contains index of all passengers who are waiting
	int waitingPassengers[noOfPassengers];		
	FILE *donePassengersFile = NULL;
	//process runs in an infinite loop and it killed with a signal by parent 
	while(1){
		kill(getpid(), SIGSTOP);
		index++;
		waitingPassengersFile = fopen("waitingPassengers.txt", "r");
		for(i = 0;i<index;i++){
				fscanf(waitingPassengersFile, "%d", &waitingPassengers[i]); 
			}
			fclose(waitingPassengersFile);
			select = rand()%index;			//randomly selects one passenger who is waiting and makes him go to restroom
			printf("RESTROOM-->Passenger %s gone to restroom\n",main_pointer[waitingPassengers[select]]->forwardFlight.ticketNo);
			sleep(2);
			printf("RESTROOM-->Passenger %s has come out of restroom\n",main_pointer[waitingPassengers[select]]->forwardFlight.ticketNo);
			donePassengersFile = fopen("donePassengers.txt", "a");
			fprintf(donePassengersFile, "%d ",waitingPassengers[select]);
			fclose(donePassengersFile);
			
			
	}
	
	}
void cafe(struct allInfo **main_pointer, int noOfPassengers){
	
	printf("CAFE IS UP AND RUNNING \n");
	
	//same logic as restroom
	int index = 0;
	int i = 0;
	int select = 0;
	FILE *waitingPassengersFile = NULL;
	int waitingPassengers[noOfPassengers];
	FILE *donePassengersFile = NULL;
	while(1){
		kill(getpid(), SIGSTOP);
		index++;
		waitingPassengersFile = fopen("waitingPassengers.txt", "r");
		for(i = 0;i<index;i++){
				fscanf(waitingPassengersFile, "%d", &waitingPassengers[i]); 
			}
			fclose(waitingPassengersFile);
			select = rand()%index;
			printf("CAFE-->Passenger %s gone to cafe\n",main_pointer[waitingPassengers[select]]->forwardFlight.ticketNo);
			sleep(2);
			printf("CAFE-->Passenger %s come out of cafe\n",main_pointer[waitingPassengers[select]]->forwardFlight.ticketNo);
			donePassengersFile = fopen("donePassengers.txt", "a");
			fprintf(donePassengersFile, "%d ",waitingPassengers[select]);
			fclose(donePassengersFile);
	}
	}
	
	
void waitingLounge(int array[], struct allInfo **main_pointer, int noOfPassengers){
		
		printf("WAITING LOUNGE IS UP AND RUNNING \n");
		int i = 0;
		int check = 0;
		int pid = 0;
		int remainingPassenger = 0;
		int select = 0;
		int children[2] = {0, 0};
		FILE *waitingPassengers = NULL;
		FILE *donePassengersFile = NULL;
		//for loop to create children
		for(i = 0;i<2;i++){
							pid = fork();
							children[i] = pid;
							if(pid == 0){
									if(i == 1){
											restRoom(main_pointer, noOfPassengers);
											exit(0);
										}
										else if(i == 0){
												cafe(main_pointer, noOfPassengers);
												exit(0);
											}
									
								}
								
					}
					
					
					//waits for signal from security check and then increases and then randomly selects one of cafe or restroom 
					//or none and makes a passenger visit it
					i = 0;
				while(i<noOfPassengers){
						kill(getpid(), SIGSTOP);
							if(passengerCheck(main_pointer[i])==1){
									printf("WAITING LOUNGE-->Passenger %s has reached waiting lounge \n",main_pointer[i]->forwardFlight.ticketNo);
									waitingPassengers = fopen("waitingPassengers.txt", "a");
									fprintf(waitingPassengers, "%d ", i);
									fclose(waitingPassengers);
									select = rand()%2;
									kill(children[select], SIGCONT);
									sleep(1);
								
								}		
							i++;
							
									
					}
					//as soon as all passengers arrive, waiting lounge stops all child processes and signals parent
					kill(children[0], SIGSTOP);
					kill(children[1], SIGSTOP);
					//after all passengers arrive, it gives signal to airport to start boarding and stops itself
					kill(getppid(), SIGCONT);	
					kill(getpid(), SIGSTOP);
					//could not do this part, hence the call is made for first passenger all the time
					printf("This is the last call for passenger %s, Please report to gate immediately \n",main_pointer[remainingPassenger]->forwardFlight.ticketNo);
					//once it receives a signal from parent that boarding has begun, it kills it children
				
					for(i = 0;i < 2; i++){
							kill(children[i], SIGKILL);
						}
				//waiting lounge after killing all children will signal boarding
				kill(array[0], SIGCONT);
				//then stop itself and wait for signal from airport to exit
				kill(getpid(), SIGSTOP);
				printf("WAITING LOUNGE EXITING, ITS CHILDREN HAVE EXITED BEFORE \n");
		
	}
