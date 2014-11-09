#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<airport.h>
#include<signal.h>

struct bag{
	int item[10];
};

typedef struct pass{
	int ret_flag;
	int entry_time[2];
	int entry_date[3];
	char ticket_no[8];
	char flight_no[6];
	int flight_time[2];
	int flight_date[3];
	char dest[15];
	char ret_ticket_no[8];
	char ret_flight_no[6];
	int ret_flight_time[2];
	int ret_flight_date[3];
	char ret_dest[15];
	char passport_no[10];
	int passport_date[3];
	char nation[15];
	int visa_date[3];
	char visa_country[15];
	char f_name[15];
	char l_name[15];
	char gender;
	int age;
	int bag_no;
	int *bag_weight;
	struct bag *bag_contents;
}pass;

void main()
{
	char c;
	int no_of_pass,i,j,k,time_check,liquid_check,explosive_check,prime_check,extra_lug_cost,seat_number,meal_type,seat_index_counter,bag_id,le_count,valid_passport,valid_visa, *wait_lng_queue,wait_lng_pop,count;
	pass *passengers;
	FILE *input_file, *curr_pass, *fopen(), *lqds_expls, *boarding_pass, *imgrtn_status, *sec_check_status, *cafe_status, *restroom_status;
	
	pid_t airport,bag_counter,imgrtn,sec_check,wait_lng,boarding,lug_sec,lug_weight,board_pass,passport_check,visa_check,sec_check_M,sec_check_F,restroom,cafe;
	
	airport = getpid();
	if((input_file = fopen("input.txt","r")) == NULL)
	{
		printf("\nCan not open input file. Now exiting\n");
		exit(1);
	}
	
	fscanf(input_file,"%d",&no_of_pass);
	passengers = (pass *)(malloc(no_of_pass*sizeof(pass)));
	
	for(i=0; i<no_of_pass; i++)
	{
		while( (c = fgetc(input_file)) == '\n' || (c = fgetc(input_file)) == '\t')
			continue;
			
		(*(passengers+i)).ret_flag = (int) c;
		if((*(passengers+i)).ret_flag == 0)
		{
			j=0;
			(*(passengers+i)).entry_time[0] = 0;
			(*(passengers+i)).entry_time[1] = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<2 )
			{
				if(c != ':')
				{
					(*(passengers+i)).entry_time[j] = (*(passengers+i)).entry_time[j]*10 + (int) c;
					continue;
				}
				else
				{
					j++;	
					continue;
				}
			}
			
			j = 0;
			(*(passengers+i)).entry_date[0] = 0;
			(*(passengers+i)).entry_date[1] = 0;
			(*(passengers+i)).entry_date[2] = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<3 )
			{
				if(c != '\\')
				{
					(*(passengers+i)).entry_date[j] = (*(passengers+i)).entry_date[j]*10 + (int) c;
					continue;
				}
				else
				{
					j++;
					continue;
				}
					
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<8)
			{
				(*(passengers+i)).ticket_no[j] = (char) c;
				j++;
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<6)
			{
				(*(passengers+i)).flight_no[j] = (char) c;
				j++;
			}
			
			j=0;
			(*(passengers+i)).flight_time[0] = 0;
			(*(passengers+i)).flight_time[1] = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<2)
			{
				if(c != ':')
				{
					(*(passengers+i)).flight_time[j] = (*(passengers+i)).flight_time[j]*10 + (int) c;
					continue;
				}
				else
				{
					j++;	
					continue;
				}
			}
			
			j = 0;
			(*(passengers+i)).flight_date[0] = 0;
			(*(passengers+i)).flight_date[1] = 0;
			(*(passengers+i)).flight_date[2] = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<3 )
			{
				if(c != '\\')
				{
					(*(passengers+i)).flight_date[j] = (*(passengers+i)).flight_date[j]*10 + (int) c;
					continue;
				}
				else
				{
					j++;
					continue;
				}
					
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<15)
			{
				(*(passengers+i)).dest[j] = (char) c;
				j++;
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<10)
			{
				(*(passengers+i)).passport_no[j] = (char) c;
				j++;
			}
			
			j = 0;
			(*(passengers+i)).passport_date[0] = 0;
			(*(passengers+i)).passport_date[1] = 0;
			(*(passengers+i)).passport_date[2] = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<3 )
			{
				if(c != '\\')
				{
					(*(passengers+i)).passport_date[j] = (*(passengers+i)).passport_date[j]*10 + (int) c;
					continue;
				}
				else
				{
					j++;
					continue;
				}
					
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<15)
			{
				(*(passengers+i)).nation[j] = (char) c;
				j++;
			}
			
			j = 0;
			(*(passengers+i)).visa_date[0] = 0;
			(*(passengers+i)).visa_date[1] = 0;
			(*(passengers+i)).visa_date[2] = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<3 )
			{
				if(c != '\\')
				{
					(*(passengers+i)).visa_date[j] = (*(passengers+i)).visa_date[j]*10 + (int) c;
					continue;
				}
				else
				{
					j++;
					continue;
				}
					
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<15)
			{
				(*(passengers+i)).visa_country[j] = (char) c;
				j++;
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<15)
			{
				(*(passengers+i)).f_name[j] = (char) c;
				j++;
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<15)
			{
				(*(passengers+i)).l_name[j] = (char) c;
				j++;
			}
			
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t'))
				(*(passengers+i)).gender = (char) c;
			
			(*(passengers+i)).age = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t'))
			{
				(*(passengers+i)).age = (*(passengers+i)).age*10 + (int) c;
			}
			
			(*(passengers+i)).bag_no = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t'))
			{
				(*(passengers+i)).bag_no = (*(passengers+i)).bag_no*10 + (int) c;
			}
			
			(*(passengers+i)).bag_weight = (int *)malloc((*(passengers+i)).bag_no * sizeof(int));
			
			j=0;
			while(j<(*(passengers+i)).bag_no)
			{
				fscanf(input_file,"%d",((*(passengers+i)).bag_weight[j]));
				j++;
			}
			
			(*(passengers+i)).bag_contents = (struct bag *)malloc(((*(passengers+i)).bag_no) * sizeof(struct bag));
			j=0;
			k=0;
			while(j<(*(passengers+i)).bag_no)
			{
				while(k<10)
				{
					fscanf(input_file,"%d",((*(passengers+i)).bag_contents[j]).item[k]);
					k++;
				}
				j++;
			}
		}
		else if((*(passengers+i)).ret_flag == 1)
		{
			j=0;
			(*(passengers+i)).entry_time[0] = 0;
			(*(passengers+i)).entry_time[1] = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<2 )
			{
				if(c != ':')
				{
					(*(passengers+i)).entry_time[j] = (*(passengers+i)).entry_time[j]*10 + (int) c;
					continue;
				}
				else
				{
					j++;	
					continue;
				}
			}
			
			j = 0;
			(*(passengers+i)).entry_date[0] = 0;
			(*(passengers+i)).entry_date[1] = 0;
			(*(passengers+i)).entry_date[2] = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<3 )
			{
				if(c != '\\')
				{
					(*(passengers+i)).entry_date[j] = (*(passengers+i)).entry_date[j]*10 + (int) c;
					continue;
				}
				else
				{
					j++;
					continue;
				}
					
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<8)
			{
				(*(passengers+i)).ticket_no[j] = (char) c;
				j++;
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<6)
			{
				(*(passengers+i)).flight_no[j] = (char) c;
				j++;
			}
			
			j=0;
			(*(passengers+i)).flight_time[0] = 0;
			(*(passengers+i)).flight_time[1] = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<2)
			{
				if(c != ':')
				{
					(*(passengers+i)).flight_time[j] = (*(passengers+i)).flight_time[j]*10 + (int) c;
					continue;
				}
				else
				{
					j++;	
					continue;
				}
			}
			
			j = 0;
			(*(passengers+i)).flight_date[0] = 0;
			(*(passengers+i)).flight_date[1] = 0;
			(*(passengers+i)).flight_date[2] = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<3 )
			{
				if(c != '\\')
				{
					(*(passengers+i)).flight_date[j] = (*(passengers+i)).flight_date[j]*10 + (int) c;
					continue;
				}
				else
				{
					j++;
					continue;
				}
					
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<15)
			{
				(*(passengers+i)).dest[j] = (char) c;
				j++;
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<8)
			{
				(*(passengers+i)).ret_ticket_no[j] = (char) c;
				j++;
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<6)
			{
				(*(passengers+i)).ret_flight_no[j] = (char) c;
				j++;
			}
			
			j=0;
			(*(passengers+i)).ret_flight_time[0] = 0;
			(*(passengers+i)).ret_flight_time[1] = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<2)
			{
				if(c != ':')
				{
					(*(passengers+i)).ret_flight_time[j] = (*(passengers+i)).ret_flight_time[j]*10 + (int) c;
					continue;
				}
				else
				{
					j++;	
					continue;
				}
			}
			
			j = 0;
			(*(passengers+i)).ret_flight_date[0] = 0;
			(*(passengers+i)).ret_flight_date[1] = 0;
			(*(passengers+i)).ret_flight_date[2] = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<3 )
			{
				if(c != '\\')
				{
					(*(passengers+i)).ret_flight_date[j] = (*(passengers+i)).ret_flight_date[j]*10 + (int) c;
					continue;
				}
				else
				{
					j++;
					continue;
				}
					
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<15)
			{
				(*(passengers+i)).ret_dest[j] = (char) c;
				j++;
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<10)
			{
				(*(passengers+i)).passport_no[j] = (char) c;
				j++;
			}
			
			j = 0;
			(*(passengers+i)).passport_date[0] = 0;
			(*(passengers+i)).passport_date[1] = 0;
			(*(passengers+i)).passport_date[2] = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<3 )
			{
				if(c != '\\')
				{
					(*(passengers+i)).passport_date[j] = (*(passengers+i)).passport_date[j]*10 + (int) c;
					continue;
				}
				else
				{
					j++;
					continue;
				}
					
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<15)
			{
				(*(passengers+i)).nation[j] = (char) c;
				j++;
			}
			
			j = 0;
			(*(passengers+i)).visa_date[0] = 0;
			(*(passengers+i)).visa_date[1] = 0;
			(*(passengers+i)).visa_date[2] = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<3 )
			{
				if(c != '\\')
				{
					(*(passengers+i)).visa_date[j] = (*(passengers+i)).visa_date[j]*10 + (int) c;
					continue;
				}
				else
				{
					j++;
					continue;
				}
					
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<15)
			{
				(*(passengers+i)).visa_country[j] = (char) c;
				j++;
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<15)
			{
				(*(passengers+i)).f_name[j] = (char) c;
				j++;
			}
			
			j=0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t') && j<15)
			{
				(*(passengers+i)).l_name[j] = (char) c;
				j++;
			}
			
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t'))
				(*(passengers+i)).gender = (char) c;
			
			(*(passengers+i)).age = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t'))
			{
				(*(passengers+i)).age = (*(passengers+i)).age*10 + (int) c;
			}
			
			(*(passengers+i)).bag_no = 0;
			while((c=fgetc(input_file)!='\n') && (c=fgetc(input_file)!='\t'))
			{
				(*(passengers+i)).bag_no = (*(passengers+i)).bag_no*10 + (int) c;
			}
			
			(*(passengers+i)).bag_weight = (int *)malloc((*(passengers+i)).bag_no * sizeof(int));
			
			j=0;
			while(j<(*(passengers+i)).bag_no)
			{
				fscanf(input_file,"%d",((*(passengers+i)).bag_weight[j]));
				j++;
			}
			
			(*(passengers+i)).bag_contents = (struct bag *)malloc(((*(passengers+i)).bag_no) * sizeof(struct bag));
			j=0;
			k=0;
			while(j<(*(passengers+i)).bag_no)
			{
				while(k<10)
				{
					fscanf(input_file,"%d",((*(passengers+i)).bag_contents[j]).item[k]);
					k++;
				}
				j++;
			}
			
				
		}
	}
	
	fclose(input_file);
	
	bag_counter = fork();
	
	if(bag_counter == 0)
	{
		lug_sec = fork();
		if(lug_sec == 0)
		{
			signal(SIGSTOP,SIG_DFL);
			signal(SIGCONT,SIG_DFL);
			signal(SIGKILL,SIG_DFL);
			raise(SIGSTOP);
			bag_id = 1000;
			while(1)
			{
				curr_pass = fopen("curr_pass.txt","r");
				fscanf("%d",&i);
				fclose(curr_pass);
				
				lqds_expls = fopen("lqds_expls.txt","w");
				le_count =0;
				for(j=0; j<(*(passengers+i)).bag_no; j++)
				{
					for(k=0; k<10; k++)
					{
						liquid_check = liquidcheck(((*(passengers+i)).bag_contents[j]).item[k]);
						explosive_check = explosivecheck(((*(passengers+i)).bag_contents[j]).item[k]);
						if(liquid_check==1 || explosive_check==1)
						{
							fprintf(lqds_expls,"%d ",((*(passengers+i)).bag_contents[j]).item[k]);
							((*(passengers+i)).bag_contents[j]).item[k] = -1;
							le_count++;
						}
					}
				}
				fclose(lqds_expls);
				kill(lug_weight,SIGCONT);
				raise(SIGSTOP);
				sleep(2);
				
				lqds_expls = fopen("lqds_expls.txt","r");
				printf("\nLiquids and explosives : ");
				while(le_count > 0)
				{
					fscanf(lqds_expls,"%d",&i);
					printf("%d ",i);
					le_count--;
				}
				boarding_pass = fopen((*(passengers+i)).ticket_no,"a");
				fprintf(boarding_pass," %d",bag_id);
				bag_id++;
				fclose(boarding_pass);
				kill(bag_counter,SIGCONT);
				raise(SIGSTOP);				
			}
		}
		else
		{
			lug_weight = fork();
			if(lug_weight == 0)
			{
				signal(SIGSTOP,SIG_DFL);
				signal(SIGCONT,SIG_DFL);
				signal(SIGKILL,SIG_DFL);
				raise(SIGSTOP);
				sleep(2);
				while(1)
				{
					curr_pass = fopen("curr_pass.txt","r");
					fscanf("%d",&i);
					fclose(curr_pass);
					
					extra_lug_cost = 0;
					if((*(passengers+i)).bag_no > 3)
					{
						extra_lug_cost = extra_lug_cost + ((*(passengers+i)).bag_no - 3) * 40;
					}
					
					j=0;
					while(j<((*(passengers+i)).bag_no))
					{
						if(((*(passengers+i)).bag_weight[j]) > 20)
							extra_lug_cost = extra_lug_cost + ((*(passengers+i)).bag_weight[j] - 20) * 2;
						j++;
					}
					
					kill(board_pass,SIGCONT);
					raise(SIGSTOP);
					sleep(2);
					printf("\nExtra amount payable : $%d",extra_lug_cost);
					boarding_pass = fopen((*(passengers+i)).ticket_no,"a");
					fprintf(boarding_pass,"$");
					fprintf(boarding_pass,"%d",extra_lug_cost);
					fclose(boarding_pass);
					
					kill(lug_sec,SIGCONT);
					raise(SIGSTOP);
				}
			}
			else
			{
				board_pass = fork();
				if(board_pass == 0)
				{
					signal(SIGSTOP,SIG_DFL);
					signal(SIGCONT,SIG_DFL);
					signal(SIGKILL,SIG_DFL);
					raise(SIGSTOP);
					sleep(2);
					
					seat_number = 1;
					seat_index_counter = 0;
					while(1)
					{
						curr_pass = fopen("curr_pass.txt","r");
						fscanf(curr_pass,"%d",&i);
						fclose(curr_pass);
						
						boarding_pass = fopen((*(passengers+i)).ticket_no,"w");
						fprintf(boarding_pass,"%s",(*(passengers+i)).f_name);
						fprintf(boarding_pass," ");
						fprintf(boarding_pass,"%s",(*(passengers+i)).l_name);
						fprintf(boarding_pass," ");
						fprintf(boarding_pass,"%d ",(*(passengers+i)).age);
						fprintf(boarding_pass,"%c ",(*(passengers+i)).gender);
						if(seat_index_counter >= 6)
						{
							seat_number++;
							seat_index_counter = 0;
						}
						fprintf(boarding_pass,"%d",seat_number);
						seat_index_counter++;
						switch((seat_index_counter))
						{
							case 0:	fprintf(boarding_pass,"A");
								break;
							case 1:	fprintf(boarding_pass,"B");
								break;
							case 2:	fprintf(boarding_pass,"C");
								break;
							case 3:	fprintf(boarding_pass,"D");
								break;
							case 4: fprintf(boarding_pass,"E");
								break;
							case 5:	fprintf(boarding_pass,"F");
								break;
							default:	break;
								
						}
						seat_index_counter++;
						fprintf(boarding_pass," ");
						meal_type = getrandom(100);
						switch((meal_type % 3))
						{
							case 0:	fprintf(boarding_pass,"Veg ");
								break;
							case 1:	fprintf(boarding_pass,"Asian Veg ");
								break;
							case 2:	fprintf(boarding_pass,"Non Veg ");
								break;
							default: break;
						}
						
						fclose(boarding_pass);
						kill(lug_weight, SIGCONT);
						raise(SIGSTOP);						
					}
				}
				else
				{
					signal(SIGSTOP,SIG_DFL);
					signal(SIGCONT,SIG_DFL);
					signal(SIGKILL,SIG_DFL);
					raise(SIGSTOP);
					sleep(2);
					while(1)
					{
						curr_pass = fopen("curr_pass.txt","r");
						fscanf(curr_pass,"%d",&i);
						fclose(curr_pass);
						
						if(i == -1)
						{
							kill(lug_sec,SIGKILL);
							kill(lug_weight,SIGKILL);
							kill(board_pass,SIGKILL);
							kill(airport,SIGCONT);
							exit(0);
						}
						
						kill(lug_sec,SIGCONT);
						raise(SIGSTOP);
						sleep(2);
						kill(airport,SIGCONT);
						raise(SIGSTOP);
					}
				}
			}
		}
	}
	else
	{
		imgrtn = fork();
		if(imgrtn == 0)
		{
			passport_check = fork();
			if(passport_check == 0)
			{
				signal(SIGCONT,SIG_DFL);
				signal(SIGSTOP,SIG_DFL);
				signal(SIGKILL,SIG_DFL);
				raise(SIGSTOP);
				sleep(2);
				while(1)
				{
					curr_pass = fopen("curr_pass.txt","r");
					fscanf(curr_pass,"%d",&i);
					fclose(curr_pass);
					
					if((*(passengers+i)).ret_flag == 1)
					{
						valid_passport = validatepassport((*(passengers+i)).ret_flight_date,(*(passengers+i)).passport_date);
					}
					else
					{
						valid_passport = validatepassport((*(passengers+i)).entry_date,(*(passengers+i)).passport_date);
					}
					
					if(valid_passport == 0)
					{
						boarding_pass = fopen((*(passengers+i)).ticket_no,"a");
						fprintf(boarding_pass," Immigration not successful");
						fclose(boarding_pass);
						
						imgrtn_status = fopen("imgrtn_status.txt","w");
						fprintf(imgrtn_status,"0");
						fclose(imgrtn_status);
						
						kill(imgrtn,SIGCONT);
						raise(SIGSTOP);						
					}
					else
					{
						kill(visa_check,SIGCONT);
						raise(SIGSTOP);
					}
				}

			}
			else
			{
				visa_check = fork();
				if(visa_check == 0)
				{
					signal(SIGCONT,SIG_DFL);
					signal(SIGSTOP,SIG_DFL);
					signal(SIGKILL,SIG_DFL);
					raise(SIGSTOP);
					sleep(2);
					while(1)
					{
						curr_pass = fopen("curr_pass.txt","r");
						fscanf(curr_pass,"%d",&i);
						fclose(curr_pass);
						
						if(strcmp((*(passengers+i)).nation,(*(passengers+i)).dest) == 0)
						{
							valid_visa = validatevisa((*(passengers+i)).visa_date,(*(passengers+i)).flight_date);
						}
						else if((*(passengers+i)).ret_flag == 1)
						{
							valid_visa = validatevisa((*(passengers+i)).visa_date,(*(passengers+i)).ret_flight_date);
						}
						else
						{
							valid_visa = validatevisa((*(passengers+i)).visa_date,(*(passengers+i)).flight_date);
						}
						
						if(valid_visa == 0)
						{
							boarding_pass = fopen((*(passengers+i)).ticket_no,"a");
							fprintf(boarding_pass," Immigration not successful");
							fclose(boarding_pass);
						
							imgrtn_status = fopen("imgrtn_status.txt","w");
							fprintf(imgrtn_status,"0");
							fclose(imgrtn_status);
						
							kill(imgrtn,SIGCONT);
							raise(SIGSTOP);
						}
						else
						{
							boarding_pass = fopen((*(passengers+i)).ticket_no,"a");
							fprintf(boarding_pass," Immigration successful");
							fclose(boarding_pass);
						
							imgrtn_status = fopen("imgrtn_status.txt","w");
							fprintf(imgrtn_status,"1");
							fclose(imgrtn_status);
						
							kill(imgrtn,SIGCONT);
							raise(SIGSTOP);
						}
					}
				}
				else
				{
					signal(SIGCONT,SIG_DFL);
					signal(SIGSTOP,SIG_DFL);
					signal(SIGKILL,SIG_DFL);
					raise(SIGSTOP);
					sleep(2);
					while(1)
					{
						curr_pass = fopen("curr_pass.txt","r");
						fscanf(curr_pass,"%d",&i);
						fclose(curr_pass);
						
						if(i == -1)
						{
							kill(passport_check,SIGKILL);
							kill(visa_check,SIGKILL);
							kill(airport,SIGCONT);
							exit(0);
						}
						
						kill(passport_check,SIGCONT);
						raise(SIGSTOP);
						sleep(2);
						
						kill(airport,SIGCONT);
						raise(SIGSTOP);
					}
				}
			}
		}
		else
		{
			sec_check = fork();
			if(sec_check == 0 )
			{
				sec_check_M = fork();
				if(sec_check_M == 0)
				{
					signal(SIGSTOP,SIG_DFL);
					signal(SIGCONT,SIG_DFL);
					signal(SIGKILL,SIG_DFL);
					raise(SIGSTOP);
					sleep(2);
					
					while(1)
					{
						curr_pass = fopen("curr_pass.txt","r");
						fscanf(curr_pass,"%d",&i);
						fclose(curr_pass);
						
						printf("\nTicket No : ");
						puts((*(passengers+i)).ticket_no);
						printf("\nDisallowed items : ");
						
						j=(*(passengers+i)).bag_no - 1;
						k=0;
						while(k<10)
						{
							liquid_check = liquidcheck(((*(passengers+i)).bag_contents[j]).item[k]);
							explosive_check = explosivecheck(((*(passengers+i)).bag_contents[j]).item[k]);
							prime_check = primecheck(((*(passengers+i)).bag_contents[j]).item[k]);
							if(liquid_check || explosive_check || prime_check)
							{
								printf("%d ",(((*(passengers+i)).bag_contents[j]).item[k]));
								(((*(passengers+i)).bag_contents[j]).item[k]) = -1;
							}
							k++;
						}
						
						kill(sec_check, SIGCONT);
						raise(SIGSTOP);						
					}
				}
				else
				{
					sec_check_F = fork();
					if(sec_check_F == 0)
					{
						signal(SIGSTOP,SIG_DFL);
						signal(SIGCONT,SIG_DFL);
						signal(SIGKILL,SIG_DFL);
						raise(SIGSTOP);
						sleep(2);
					
						while(1)
						{
							curr_pass = fopen("curr_pass.txt","r");
							fscanf(curr_pass,"%d",&i);
							fclose(curr_pass);
						
							printf("\nTicket No : ");
							puts((*(passengers+i)).ticket_no);
							printf("\nDisallowed items : ");
						
							j=(*(passengers+i)).bag_no - 1;
							k=0;
							while(k<10)
							{
								liquid_check = liquidcheck(((*(passengers+i)).bag_contents[j]).item[k]);
								explosive_check = explosivecheck(((*(passengers+i)).bag_contents[j]).item[k]);
								prime_check = primecheck(((*(passengers+i)).bag_contents[j]).item[k]);
								if(liquid_check || explosive_check || prime_check)
								{
									printf("%d ",(((*(passengers+i)).bag_contents[j]).item[k]));
									(((*(passengers+i)).bag_contents[j]).item[k]) = -1;
								}
									k++;
							}
						
							kill(sec_check, SIGCONT);
							raise(SIGSTOP);
						}
					}
					else
					{
						signal(SIGSTOP,SIG_DFL);
						signal(SIGCONT,SIG_DFL);
						signal(SIGKILL,SIG_DFL);
						raise(SIGSTOP);
						sleep(2);
						while(1)
						{
							curr_pass = fopen("curr_pass.txt","r");
							fscanf(curr_pass,"%d",&i);
							fclose(curr_pass);
							
							if(i == -1)
							{
								kill(sec_check_M,SIGKILL);
								kill(sec_check_F,SIGKILL);
								kill(airport,SIGCONT);
								exit(0);
							}
							
							imgrtn_status = fopen("imgrtn_status.txt","r");
							if((int) fgetc(imgrtn_status) == 0)
							{
								sec_check_status = fopen("sec_check_status.txt","w");
								fprintf(sec_check_status,"0");
								fclose(sec_check_status);
								kill(airport,SIGCONT);
								raise(SIGSTOP);
							}
							else
							{
								if((*(passengers+i)).gender == 'M' || (*(passengers+i)).gender == 'm')
								{
									kill(sec_check_M,SIGCONT);
									raise(SIGSTOP);
									sleep(2);
									sec_check_status = fopen("sec_check_status.txt","w");
									fprintf(sec_check_status,"1");
									fclose(sec_check_status);
									kill(airport,SIGCONT);
									raise(SIGSTOP);
								}
								else if((*(passengers+i)).gender == 'F' || (*(passengers+i)).gender == 'f')
								{
									kill(sec_check_F,SIGCONT);
									raise(SIGSTOP);
									sleep(2);
									sec_check_status = fopen("sec_check_status.txt","w");
									fprintf(sec_check_status,"1");
									fclose(sec_check_status);
									kill(airport,SIGCONT);
									raise(SIGSTOP);
								}
							}
							
						}
					}
				}
				
			}
			else
			{
				wait_lng = fork();
				if(wait_lng == 0)
				{
					cafe = fork();
					if(cafe == 0)
					{
						signal(SIGSTOP,SIG_DFL);
						signal(SIGCONT,SIG_DFL);
						signal(SIGKILL,SIG_DFL);
						raise(SIGSTOP);
						while(1)
						{
							cafe_status = fopen("cafe_status.txt","r");
							fscanf(cafe_status,"%d",&i);
							fclose(cafe_status);
							
							printf("\nPassenger ");
							puts((*(passengers+i)).ticket_no);
							printf(" entered Cafe");
							
							sleep(1);
							kill(wait_lng, SIGCONT);
							raise(SIGSTOP);
						}
					}
					else
					{
						restroom = fork();
						if(restroom == 0)
						{
							signal(SIGSTOP,SIG_DFL);
							signal(SIGCONT,SIG_DFL);
							signal(SIGKILL,SIG_DFL);
							raise(SIGSTOP);
							while(1)
							{
								restroom_status = fopen("restroom_status.txt","r");
								fscanf(restroom_status,"%d",&i);
								fclose(restroom_status);
								
								printf("\nPassenger ");
								puts((*(passengers+i)).ticket_no);
								printf(" entered Restroom");
								
								sleep(1);
								kill(wait_lng, SIGCONT);
								raise(SIGSTOP);
							}
						}
						else
						{
							signal(SIGSTOP,SIG_DFL);
							signal(SIGCONT,SIG_DFL);
							signal(SIGKILL,SIG_DFL);
							raise(SIGSTOP);
							sleep(2);
							wait_lng_pop = 0;
							wait_lng_queue = (int *)malloc(no_of_pass*sizeof(int));
							j=0;
							while(1)
							{
								curr_pass = fopen("curr_pass.txt","r");
								fscanf(curr_pass,"%d",&i);
								fclose(curr_pass);
								
								if(i == -1)
								{
									k = getrandom(j);
									i = getrandom(2);
									
									if(i==0)
									{
										cafe_status = fopen("cafe_status.txt","w");
										fprintf(cafe_status,"%d",*(wait_lng_queue + k));
										fclose(cafe_status);
										kill(cafe,SIGCONT);
										raise(SIGSTOP);
									}
									else
									{
										restroom_status = fopen("restroom_status.txt","w");
										fprintf(restroom_status,"%d",*(wait_lng_queue + k));
										fclose(restroom_status);
										kill(restroom,SIGCONT);
										raise(SIGSTOP);
									}
									
									kill(airport,SIGCONT);
								}
								else if(i == -2)
								{
									kill(cafe,SIGKILL);
									kill(restroom,SIGKILL);
									kill(airport,SIGCONT);
									exit(0);
								}
								else
								{
									*(wait_lng_queue + j) = i;
									j++;
									wait_lng_pop++;
									
									k = getrandom(j);
									i = getrandom(2);
									
									if(i==0)
									{
										cafe_status = fopen("cafe_status.txt","w");
										fprintf(cafe_status,"%d",*(wait_lng_queue + k));
										fclose(cafe_status);
										kill(cafe,SIGCONT);
										raise(SIGSTOP);
									}
									else
									{
										restroom_status = fopen("restroom_status.txt","w");
										fprintf(restroom_status,"%d",*(wait_lng_queue + k));
										fclose(restroom_status);
										kill(restroom,SIGCONT);
										raise(SIGSTOP);
									}
									
									kill(airport,SIGCONT);
			
								
								}
							}
						}
					}
				}
				else
				{
					boarding = fork();
					if(boarding == 0)
					{
						signal(SIGSTOP,SIG_DFL);
						signal(SIGCONT,SIG_DFL);
						signal(SIGKILL,SIG_DFL);
						raise(SIGSTOP);
						
						printf("\nAll passengers are requested to move to the gate");
						kill(airport,SIGCONT);
						raise(SIGSTOP);
					}
					else
					{
						i=0;
						j=0;
						k=0;
						count = 0;
						for(i=0; i<no_of_pass; i++)
						{
							time_check = timecheck((*(passengers+i)).entry_time,(*(passengers+i)).flight_time);
							if(time_check == 0)
								continue;
							else
							{
								curr_pass = fopen("curr_pass.txt","w");
								fprintf(curr_pass,"%d",i);
								fclose(curr_pass);
								kill(bag_counter, SIGCONT);
								raise(SIGSTOP);
								sleep(2);
								kill(imgrtn,SIGCONT);
								raise(SIGSTOP);
								sleep(2);
								
								imgrtn_status = fopen("imgrtn_status.txt","r");
								fscanf(imgrtn_status,"%d",&i);
								if(i == 0);
									continue;
								kill(sec_check,SIGCONT);
								raise(SIGSTOP);
								sleep(2);
								
								sec_check_status = fopen("sec_check_status.txt","r");
								fcanf(sec_check_status,"%d",&i);
								if(i==0)
									continue;
								kill(wait_lng,SIGCONT);
								count++;
								raise(SIGSTOP);
							}
						}
						j= -1;
						curr_pass = fopen("curr_open.txt","w");
						fprintf(curr_pass,"%d",j);
						fclose(curr_pass);
						
						kill(bag_counter,SIGCONT);
						raise(SIGSTOP);
						kill(imgrtn,SIGCONT);
						raise(SIGSTOP);
						kill(sec_check,SIGCONT);
						raise(SIGSTOP);
						kill(boarding,SIGCONT);
						raise(SIGSTOP);
						
						j= -2;
						curr_pass = fopen("curr_open.txt","w");
						fprintf(curr_pass,"%d",j);
						fclose(curr_pass);
						raise(SIGSTOP);
						
						printf("\n\n\nTotal number of passengers arrived : %d",no_of_pass);
						printf("\nTotal number of passengers boarded : %d",count);
						
						printf("\nFlight number %d ready to depart with %d passengers",getpid(),count);
						printf("\nThe plane flew....");
						
						kill(boarding,SIGKILL);
						exit(0);
					}
				}
			}
		}
	}
	
	
}
