#include "header.h"
extern void airport(struct flyers ** array,int entries)
{
	//struct flyer **array=*n1;
	int i,j,k,r,ret1=1,ret2,flag=0;
	pid_t b1,						//baggage
		      ls,w,pass,			//luggage security, weight checking, boarding pass
		  imm,						//immigration
		      vis,passp,			//visa, passport
		  s,						//security
		      m,f,					//male female security check
		  lou,						//lounge
		  	caf,rest,				//cafe, restroom
		  b2;						//boarding
	
		b1=fork();
		if(b1==0)
		{
			printf("Inside baggage with pid: %d\n",getpid());
			ls=fork();
			if(ls==0)
			{
				printf("Inside luggage_security with pid: %d\n",getpid());
				for(i=0;i<entries;i++)
				{
				for(j=0;j<array[i]->total_bags;j++)
				{
						for(k=0;k<10;k++)
						{
							ret1=colorful(array[i]->bag_contents[j][k]);
							if(ret1==1)
							{
								flag=1;
								printf("object:  %d ***Danger*** LIQUID FOUND should be removed from luggage\n",array[i]->bag_contents[j][k]);	
								ret1=0;
							}
							ret2=palindrome(array[i]->bag_contents[j][k]);
							if(ret2==1)
							{
								printf("object: %d ***Danger***, EXPLOSIVE FOUND should be removed from luggage\n",array[i]->bag_contents[j][k]);
								ret2=0;
							}
						}
				}
				}
				if(!flag)
				{
					printf("All Clear\n");
				}
				
				exit(0);	
			}
			w=fork();
			if(w==0)
			{
				//printf("Inside baggage_weight with pid: %d\n",getpid());
				exit(0);	
			}
			pass=fork();
			if(pass==0)
			{
				//printf("Inside baggage_boarding_pass with pid: %d\n",getpid());
				exit(0);	
			}
			while(wait(NULL)!=-1);
			exit(0);
		}
		imm=fork();
		if(imm==0)
		{
			//printf("Inside Immigration with pid: %d\n",getpid());
			vis=fork();
			if(vis==0)
			{
				//printf("Inside visa with pid: %d\n",getpid());
				exit(0);	
			}
			passp=fork();
			if(passp==0)
			{
				//printf("Inside passport with pid: %d\n",getpid());
				exit(0);	
			}
			while(wait(NULL)!=-1);
			exit(0);
		}
		s=fork();
		if(s==0)
		{
			//printf("\n\nxxxxx%cxxxxx\n\n",array[0]->gender);
			printf("Inside Security with pid: %d\n",getpid());
			
			if(1)
			{
				m=fork();
				if(m==0)
				{
					printf("Inside final Baggage Check for Handbag with pid: %d\n",getpid());
					for(i=0;i<entries;i++)
					
						for(j=0;j<array[i]->total_bags;j++)
						{
							for(k=0;k<10;k++)
							{
								ret1=prime(array[i]->bag_contents[j][k]);
								if(ret1)
								printf("Object: %3d For Security Reasons it has to be removed from hand bag\n\n",array[i]->bag_contents[j][k]);
							}
						}
					
						exit(0);	
				}
			}
			else
			{
				f=fork();
				if(f==0)
				{
					printf("Inside s_female with pid: %d\n",getpid());
					exit(0);	
				}
			}
			while(wait(NULL)!=-1);
			exit(0);
		}
		lou=fork();
		if(lou==0)
		{
			//printf("Inside lounge with pid: %d\n",getpid());
			
			caf=fork();
			if(caf==0)
			{
				//printf("Inside cafe with pid: %d\n",getpid());
				exit(0);	
			}
			rest=fork();
			if(rest==0)
			{
				//printf("Inside restroom with pid: %d\n",getpid());
				exit(0);	
			}
			exit(0);
		}
		b2=fork();
		if(b2==0)
		{
			//printf("Inside boarding with pid: %d\n",getpid());
			exit(0);
		}
		while(wait(NULL)!=-1);
	
}
