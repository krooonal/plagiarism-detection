#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
struct flyers
{
	int flag;
	int age;
	int total_bags;
	
	char r_tkt_no[10];
	char r_flt_no[7];
	int r_flt_timeh;
	int r_flt_timem;
	int r_flt_date_d;
	int r_flt_date_m;
	int r_flt_date_y;
	char r_dest[25]; 
	int ent_timeh;
	int ent_timem;
	int ent_date_d;
	int ent_date_m;
	int ent_date_y;
	char tkt_no[10];
	char flt_no[7];
	//int flt_time[10];
	int flt_timem;
	int flt_timeh;
	int flt_date_d;
	int flt_date_m;
	int flt_date_y;
	char dest[25];
	char pass_no[10];
	//char pass_time[10];
	int pass_date_d;
	int pass_date_m;
	int pass_date_y;
	char pass_nation[25];
	int visa_exp_d;
	int visa_exp_m;
	int visa_exp_y;
	char vis_country[25];
	char f_name[25],l_name[25],gender;
	int *bag_weight;
	int **bag_contents;
};
extern void input(struct flyers ** array,int entries,FILE *f );
extern void airport(struct flyers ** n1,int entries);
extern int colorful(int num);
extern int palindrome(int num);
extern int prime(int num);
