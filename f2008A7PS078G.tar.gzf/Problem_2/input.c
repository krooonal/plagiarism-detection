#include "header.h"
extern void input(struct flyers ** array,int entries,FILE *f )
{
	int i,j,k,n;
	for(i=0;i<entries;i++)
	{
			fscanf(f,"%d",&array[i]->flag);
				//printf("%d %d\n",i,array[i]->flag);
			fscanf(f,"%d:%d %d/%d/%d",&array[i]->ent_timeh,&array[i]->ent_timem,&array[i]->ent_date_d,&array[i]->ent_date_m,&array[i]->ent_date_y);
				
			fscanf(f,"%s %s %d:%d %d/%d/%d %s",array[i]->tkt_no,array[i]->flt_no,&array[i]->flt_timeh,&array[i]->flt_timem,&array[i]->flt_date_d,&array[i]->flt_date_m,&array[i]->flt_date_y,array[i]->dest);
		
			if(array[i]->flag==1)
			{
				fscanf(f,"%s %s %d:%d  %d/%d/%d %s",array[i]->r_tkt_no,array[i]->r_flt_no,&array[i]->r_flt_timeh,&array[i]->r_flt_timem,&array[i]->r_flt_date_d,&array[i]->r_flt_date_m,&array[i]->r_flt_date_y,array[i]->r_dest);
			
			}
			fscanf(f,"%s %d/%d/%d %s\n",array[i]->pass_no,&array[i]->pass_date_d,&array[i]->pass_date_m,&array[i]->pass_date_y,array[i]->pass_nation);
			fscanf(f,"%d/%d/%d %s",&array[i]->visa_exp_d,&array[i]->visa_exp_m,&array[i]->visa_exp_y,array[i]->vis_country);
			fscanf(f,"%s %s %c %d",array[i]->f_name,array[i]->l_name,&array[i]->gender,&array[i]->age);
			//printf("*****%c*****",array[i]->gender);
			fscanf(f,"%d ",&array[i]->total_bags);
			array[i]->bag_weight=(int *)malloc(array[i]->total_bags*sizeof (int));
			for(j=0;j<array[i]->total_bags;j++)
			{
				fscanf(f,"%d",&array[i]->bag_weight[j]);	
			}
			array[i]->bag_contents=(int **)malloc(array[i]->total_bags*sizeof (int*));
			
			for(j=0;j<array[i]->total_bags;j++)
			{
				array[i]->bag_contents[j]=(int *)malloc(10*sizeof (int));
						
			}
			for(j=0;j<array[i]->total_bags;j++)
			{
				for(k=0;k<10;k++)
				{
					fscanf(f,"%d",&array[i]->bag_contents[j][k]);
					
				}
			}
			//printf("hello world3\n");
			/*for(j=0;j<array[i]->total_bags;j++)
			{
				for(k=0;k<10;k++)
				{
					printf(" %3d ",array[i]->bag_contents[j][k]);		
				}
				printf("\n");
			}*/
			
		//}
		
		/*printf(" hello: %d:%d  %d:%d",array[i]->ent_timeh,array[i]->ent_timem,array[i]->flt_timeh,array[i]->flt_timem);
		printf("%d/%d/%d\n",array[i]->ent_date_d,array[i]->ent_date_m,array[i]->ent_date_y);
		if(array[i]->flag==1)	
		{
			printf("  %d:%d\n",array[i]->r_flt_timeh,array[i]->r_flt_timem);
		}
		else	
		printf("Invalid Input\n");	*/		
	}
	fclose(f);
	//printf("hello world4\n");
	
}
