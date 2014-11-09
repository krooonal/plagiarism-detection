


void boarding(int array[], struct allInfo **main_pointer, int noOfPassengers){
		printf("BOARDING IS UP AND RUNNING \n");
	
		kill(getpid(), SIGSTOP);
		
		//once boarding receives signal from airport, it begins boarding
		printf("All passengers are requested to head to gate for boarding \n");
		sleep(2);
		//after waiting for 2 sec, it tells airport to tell waiting lounge to tell passengers that this is the last call
		kill(getppid(), SIGCONT);
		//it then waits for confirmation from waiting lounge
		kill(getpid(), SIGSTOP);
		//it then tells airport that boarding is done and to start shutdown process
		kill(getppid(), SIGCONT);
		//then waits for signal from airport to exit
		kill(getpid(), SIGSTOP);
		printf("BOARDING EXITING \n");
	}
