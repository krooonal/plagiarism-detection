

//this file contains the process immigration and all of its children, namely passport and visa


void passport(struct allInfo **main_pointer, int noOfPassengers, int visapid){
		printf("PASSPORT IS UP AND RUNNING \n");
		
		int i = 0;
		
		
		//process after creation, enters while loop and then stops itself to wait for signal from parent to process the next passenger
		while(i<noOfPassengers){
		kill(getpid(), SIGSTOP);
		printf("PASSPORT-->Passport is processing %s\n",main_pointer[i]->forwardFlight.ticketNo);
		FILE *print = fopen(main_pointer[i]->forwardFlight.ticketNo, "a");
		int result = passportCheck(main_pointer[i], print);
		fclose(print);
		i++;
	}
	//once all passengers are through, then stops itself and waits for signal from parent to exit
	kill(getpid(), SIGSTOP);
	printf("PASSPORT EXITING \n");
	}
	

void visa(struct allInfo **main_pointer, int noOfPassengers){
		printf("VISA IS UP AND RUNNING \n");
		
		
		int i = 0;
		
		//process stops itself after processing one passenger and waits for signal from parent to continue
		while(i<noOfPassengers){
		kill(getpid(), SIGSTOP);
		printf("VISA-->Visa is processing %s\n",main_pointer[i]->forwardFlight.ticketNo);
		int check = 0;
		check = passengerCheck(main_pointer[i]);
		if(check){
				FILE *print = fopen(main_pointer[i]->forwardFlight.ticketNo, "a");
				visaCheck(main_pointer[i], print);
				fclose(print);
			}
		i++;
	}
	
	//once all passengers are through, then stops itself and waits for signal from parent to exit
	kill(getpid(), SIGSTOP);	
	printf("VISA EXITING \n");
	
	}

void immigration(int array[], struct allInfo **main_pointer, int noOfPassengers){
		printf("IMMIGRATION IS UP AND RUNNING \n");
		
		
		int children[2] = {0}; //array to store all pid's of children
		int i = 0;
		int pid = 0;
		
		//for loop to create all children
		
		for(i = 0;i<2;i++){
							pid = fork();
							children[i] = pid;
							if(pid == 0){
									if(i == 1){
											passport(main_pointer, noOfPassengers, children[0]);
											exit(0);
										}
										else if(i == 0){
												visa(main_pointer, noOfPassengers);
												exit(0);
											}
									
								}
								
					}
					sleep(1);
					//once all children have been created process stops itself and waits for signal from baggage counter to
					//process the passenger the baggage counter has just finished
					i = 0;
					while(i<noOfPassengers){
						kill(getpid(), SIGSTOP);
						
						printf("IMMIGRATION-->Immigration is processing %s\n",main_pointer[i]->forwardFlight.ticketNo);
						
						
						kill(children[1], SIGCONT);			//process delegates task to passport and then sleeps for 2 seconds
						sleep(1);							//after 1 second it is assumed that passport has finished the task
						
						
						
						kill(children[0], SIGCONT);			//same logic as passport
						sleep(1);
						
					//once visa processes the passenger, the process signals security to start and process the passenger it has just 
					//finished processing and moves onto the next passenger itself	
					kill(array[2], SIGCONT);
					sleep(2);
					i++;
				}
					//after finishing all passengers, it waits for airport to signal it to exit and then tells children to exit and 
					//then exits
					kill(getpid(), SIGSTOP);
					kill(children[0], SIGCONT);
					kill(children[1], SIGCONT);
					while(wait(NULL)!=-1);
					printf("IMMIGRATION EXITING \n");
			
	}
	

