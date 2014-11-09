#include "header.h"
extern int colorful(int num)
{
	int t=0,count=0,i=0,j=0,k =0,l=0;			//t-> variable for holding temporary values, i,j loop variables, 
	t=num;										//count holds the total digits in the number
	while(t>0)									//loop to find the number of digits in the integer		
	{
		t=t/10;
		count++;	
	}
	int a[count];								//Declare an array to store individual digits which is used for further computation
	t=num;
	for(i=0;i<count;i++)						//segregating each digit of num into the array a[]
	{	
		a[i]=t%10;
		t=t/10;
	}
	l=(count*(count+1))/2;
	int pr_s[count][count], pr_s_l[l];			//pr_s-> 2-D array storing the substrings and the required product of substrings
												//pr_s_l-> Array storing the upper trangular entries in a linear form for easy comparison
	for (i = 0; i < count; i++)					//Setting the Diagonal elements as the individual digits itself
	{
		pr_s[i][i] = a[i];		
	}
	for( i = 0; i<count-1; i++)			//finding the upper triangular matrix, which contains all the 
	{						//possible products of substrings
		for (j= i+1; j<count ; j++)    		//Eg1. if entry is 234
		{					//    
			pr_s[i][j] = pr_s[i][j-1]*a[j];	//    the resultant matrix can be found by putting 2,3,4 in the diagonal
		}					//    a-> [2,3,4]
							//    2	    3    4
	}						//    |	    |    |
							//    v	    v    v
							//    2--->2x3->2x3x4
							//	    	  
							//  	    	  
							//    x     3--->3x4  
	for ( i = 0; i<count; i++)			//		 
	{						//		 
		for (j=i; j<count; j++)			//    x     x    4
 		{					//
							// x-> we need not care
			pr_s_l[k] = pr_s[i][j];		//   the elements of pr_s_l therefore are 2,3,4,6,12,24 from the above matrix
							//Eg2. for input 2347 the array a[] becomes [2 3 4 7]
			k++;				//    2     3     4     7   
		} 					//    |     |     |     |
	}						//    v     v     v     v
							//    2-->2x3->2x3x4->2x3x4x7
							//    	
		                                        //    x     3 ->3x4-->3x4x7
							//    
	for(i = 0 ; i<l; i++)				//    x     x     4--> 4x7
	{						//
		for(j=i+1;j<l;j++)			//    x     x     x     7
			if( pr_s_l[i] == pr_s_l[j] )	//
			return 0;			//  The elements of the pr_s_l therefore are 2,3,6,7,6,12,42,
	}
	return 1;
}
