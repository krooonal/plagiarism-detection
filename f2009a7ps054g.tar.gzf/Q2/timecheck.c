#include<stdio.h>

extern int timecheck(int *e_time,int *f_time)
{
	int mins, hours;
	if(f_time[1] < e_time[1])
	{
		f_time[0]--;
		f_time[1] = f_time[1] + 60;
	}
	mins = f_time[1] - e_time[1];
	
	if(f_time[0] < e_time[0])
	{
		hours = 24 + f_time[0] - e_time[0];
	}
	if(hours >=4 && mins >=0)
		return 0;
	else
		return 1;
}
