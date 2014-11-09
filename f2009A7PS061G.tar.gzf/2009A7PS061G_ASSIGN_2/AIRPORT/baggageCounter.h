
//this file contains the process baggage counter and all of its children namely luggage security, weight and boarding pass



void luggageSecurityProcess(struct allInfo **main_pointer, int noOfPassengers){
			printf("LUGGAGE SECURITY IS UP AND RUNNING \n");
	
			int i = 0;

			//process stops just after creating itself and waits for baggage counter to continue it to take first passenger
			kill(getpid(), SIGSTOP);
			
			
			//in this while loop the process processes one single passenger stops itself, waits for its sibling to finish
			//and then finishes itself and stops till the parent tells it to start again
			while(i<noOfPassengers){
			
			
			
			luggageSecurityFunction(main_pointer[i]);
			kill(getppid(), SIGCONT);	//signals parent to start weight
			kill(getpid(), SIGSTOP);	//stops itself
			sleep(1);
			luggageSecurityAfter(main_pointer[i]);
			kill(getppid(), SIGCONT);	//signals parent to start weight
			kill(getpid(), SIGSTOP);	//stops itself
			sleep(1);
			i++;	
		}
		
		
		//once all passengers are through the process is still stopped inside the loop itself and waits for the parent to signal it
		//to exit, once this happens the loop increments i, comes out of loop and exits
		printf("LUGGAGE SECURITY EXITING \n");
		

		
	}
void weightProcess(struct allInfo **main_pointer, int noOfPassengers){
		printf("WEIGHT IS UP AND RUNNING \n");
		

		int i = 0;
		
		
		//process stops just after creating itself and waits for baggage counter to continue it to take first passenger
		kill(getpid(), SIGSTOP);
		
		//in this while loop the process processes one single passenger, stops itself, waits for its sibling to finish
		//and then finishes itself and stops till the parent tells it to start again
		while(i<noOfPassengers){
		
		int extra  = weightFunction(main_pointer[i]);
		kill(getppid(), SIGCONT);				//signals parent to start boarding pass
		kill(getpid(), SIGSTOP);				//stops itself
		sleep(1);
		printf("WEIGHT-->WEIGHT is generating ticketNo %s \n",main_pointer[i]->forwardFlight.ticketNo);
		FILE *print = fopen(main_pointer[i]->forwardFlight.ticketNo, "a");
		fprintf(print, "extra is %d ",extra);
		fclose(print);
		kill(getppid(), SIGCONT);
		
		kill(getpid(), SIGSTOP);
		sleep(1);
		i++;
		}
		
		//once all passengers are through the process is still stopped inside the loop itself and waits for the parent to signal it
		//to exit, once this happens the loop increments i, comes out of loop and exits
		printf("WEIGHT EXITING \n");
		
	
	}
void boardingPassProcess(struct allInfo **main_pointer, int noOfPassengers){
		printf("BOARDING PASS IS UP AND RUNNING \n");
		
		
		int i = 0;
		
		
		//process stops just after creating itself and waits for baggage counter to continue it to take first passenger
		kill(getpid(), SIGSTOP);
		
		//in this while loop the process processes one single passenger, stops itself, and signals parent to start its siblings
		while(i<noOfPassengers){
			
		FILE *print = fopen(main_pointer[i]->forwardFlight.ticketNo, "w");
		boardingPassFunction(main_pointer[i], print);
		fclose(print);
		kill(getppid(), SIGCONT);		//tells parent to start weight
		
			kill(getpid(), SIGSTOP);	//stops itself
			sleep(1);
			i++;
		}
		
		
		//once all passengers are through the process is still stopped inside the loop itself and waits for the parent to signal it
		//to exit, once this happens the loop increments i, comes out of loop and exits
		printf("BOARDING PASS EXITING \n");
	
	}
void baggageCounter(int array[], struct allInfo **main_pointer, int noOfPassengers){
	
	
				printf("BAGGAGE COUNTER IS UP AND RUNNING \n");
				
				
				
				
				FILE *pidvalues;
				int children[3] = {0};				//array to maintain pid values of children
				int i = 0;
				int pid = 0;
				
				
				
				//for loop to create children
				for(i = 0;i<3;i++){
							pid = fork();
							children[i] = pid;
							if(pid == 0){
									if(i == 0){
											luggageSecurityProcess(main_pointer, noOfPassengers);
											exit(0);
										}
										else if(i == 1){
												weightProcess(main_pointer, noOfPassengers);
												exit(0);
											}
										else if(i == 2){
												boardingPassProcess(main_pointer, noOfPassengers);
												exit(0);
											}
									
								}
								
					}
					//creates children stops itself and waits for airport to start it
					kill(getpid(), SIGSTOP);
					i = 0;
					
					while(i<noOfPassengers){
						
					printf("Baggage is awake with passsenger %s \n", main_pointer[i]->personal.firstName);
					//starts luggage security and stops itself
					kill(children[0], SIGCONT);
					kill(getpid(), SIGSTOP);
					sleep(1);
					
					
					//once signal from luggage security is received, starts weight and stops itself
					kill(children[1], SIGCONT);
					kill(getpid(), SIGSTOP);
					sleep(1);
					
					
					//once signal from weight is received, starts boarding pass and stops itself
					kill(children[2], SIGCONT);
					kill(getpid(), SIGSTOP);
					sleep(1);
					
					
					//once signal from boarding pass is received, starts weight and stops itself
					kill(children[1], SIGCONT);
					kill(getpid(), SIGSTOP);
					sleep(1);
					
					
					//once signal from weight is received, starts luggage security and stops itself
					kill(children[0], SIGCONT);
					kill(getpid(), SIGSTOP);
					
					//once signal from luggage security is received, starts immigration to process the passenger it has just finished
					//and then moves onto the next passenger itself
					kill(array[3], SIGCONT);
					i++;
					
				}
				//once all passengers have finished it waits for signal from airport, once it gets that, it tells all children to exit
				//then after children have exit, it exits
				kill(getpid(), SIGSTOP);
				kill(children[0], SIGCONT);
				kill(children[1], SIGCONT);
				kill(children[2], SIGCONT);
				while(wait(NULL)!=-1);
				printf("BAGGAGE COUNTER EXITING \n");
				
				
				
	}
