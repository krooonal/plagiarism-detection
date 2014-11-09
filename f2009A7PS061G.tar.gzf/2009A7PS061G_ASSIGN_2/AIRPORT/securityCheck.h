

//this file contains the process securityCheck and its children male and female security


void maleSecurity(struct allInfo **main_pointer, int noOfPassengers){
	
	printf("MALE SECURITY IS UP AND RUNNING \n");
	
	
	int i = 0;
	int check  = 0;
		//process processes one passenger and then waits for parent to give it the next passenger
		while(i<noOfPassengers){
					kill(getpid(), SIGSTOP);
					check = passengerCheck(main_pointer[i]);     	//first it check whether passenger has cleared immigration, 
																	//if not, it throws passenger out of airport
					if(main_pointer[i]!=NULL){
						if(main_pointer[i]->personal.gender == 'M' && check == 1){ //it checks if passenger is male, if not,
								printf("MALE SECURITY-->Male security is processing %s\n",main_pointer[i]->forwardFlight.ticketNo);												//it doe nothing
								handBagCheck(main_pointer[i]);
							}
						if(check == 0 && main_pointer[i]->personal.gender == 'M'){
								printf("MALE SECURITY-->Male security is processing %s\n",main_pointer[i]->forwardFlight.ticketNo);
								printf("male passenger %s has been thrown out of airport \n",main_pointer[i]->personal.firstName);
								main_pointer[i] = NULL;
							}
					}
						i++;
			}
			//after last passenger has been processed, it waits for signal from parent to exit then exits
			kill(getpid(), SIGSTOP);
			printf("MALE SECURITY EXITING \n");
		
	}


void femaleSecurity(struct allInfo **main_pointer, int noOfPassengers){
	printf("FEMALE SECURITY IS UP AND RUNNING \n");
	
	//same logic as male security
	int i = 0;
	int check = 0;
		while(i<noOfPassengers){
					kill(getpid(), SIGSTOP);
					
					if(main_pointer[i]!=NULL){
						check = passengerCheck(main_pointer[i]);
						if(main_pointer[i]->personal.gender == 'F' && check == 1){
								printf("FEMALE SECURITY-->Female security is processing %s\n",main_pointer[i]->forwardFlight.ticketNo);
								handBagCheck(main_pointer[i]);
							}
						if(check == 0 && main_pointer[i]->personal.gender == 'F'){
								printf("FEMALE SECURITY-->Female security is processing %s\n",main_pointer[i]->forwardFlight.ticketNo);
								main_pointer[i] = NULL;
							}
					}
						i++;
			}
			kill(getpid(), SIGSTOP);
			printf("FEMALE SECURITY EXITING \n");
	}
void securityCheck(int array[], struct allInfo **main_pointer, int noOfPassengers){
	
		printf("SECURITY CHECK IS UP AND RUNNING \n");
		
		
		int i = 0;
		int pid = 0;
		int children[2] = {0};		//array to store children
		
		//for loop to create children
			for(i = 0;i<2;i++){
							pid = fork();
							children[i] = pid;
							if(pid == 0){
									if(i == 1){
											maleSecurity(main_pointer, noOfPassengers);
											exit(0);
										}
										else if(i == 0){
												femaleSecurity(main_pointer, noOfPassengers);
												exit(0);
											}
									
								}
								
					}
					i = 0;
					//processes one passenger and then stops itself till immigration tells it to start
					while(i<noOfPassengers){
						
							kill(getpid(), SIGSTOP);
							
							printf("SECUTIY CHECK-->Security check is processing %s\n",main_pointer[i]->forwardFlight.ticketNo);
							kill(children[0], SIGCONT);		//starts both male and female security for same passenger , no clashes 
							kill(children[1], SIGCONT);		//occur because the children will not process a passenger if the gender															
															//does not match, after delegating the task it sleeps for a second
															//after which it is assumed the children have finished the task
							
							
							
							sleep(2);
							kill(array[1], SIGCONT);	//signals waiting lounge to tell it that one more passenger has arrived
							i++;						//then moves onto the next passenger
							
						}
						
						
						//after finishing all passengers, it waits for airport to signal it to exit and then tells children  
						//to exit and then exits
						
						
						kill(getpid(), SIGSTOP);
						kill(children[0], SIGCONT);
						kill(children[1], SIGCONT);
						while(wait(NULL)!=-1);
						printf("SECURITY CHECK EXITING \n");
						
	}
