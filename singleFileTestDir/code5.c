#include <stdio.h>
#include <stdlib.h>
void merge(int array[] , int lb , int ub)
{
	int mb = (lb + ub)/2;
	int n1 = mb-lb +1;
	int n2 = ub - mb;
	int i=0 , j , *L , *R , k=lb;
	L = (int *)malloc(n1 * sizeof(int));
	R = (int *)malloc(n2 * sizeof(int));
	for(j=lb ; j<=mb ; j++)
		L[i++] = array[j];
	i=0;
	for(j=mb+1 ; j<=ub ; j++)
		R[i++] = array[j];

	i=0; 
	j=0;
	while(i<n1 && j<n2)
	{
		if(L[i] <= R[j])
			array[k++] = L[i++];
		else
			array[k++] = R[j++];
	}
	while(i<n1)
		array[k++] = L[i++];
	while(j<n2)
		array[k++] = R[j++];
}
void mergeSort(int array[] , int lb , int ub)
{
	if(lb < ub)
	{
		int mb = (lb + ub)/2;
		mergeSort(array , lb , mb);
		mergeSort(array ,mb+1 , ub);
		merge(array , lb , ub);
	}
}

int Bsearch(int array[] , int lb , int ub , int key)
{
	if(lb == ub)
		return lb;
	int mid = (lb + ub)/2;
	if(array[mid] > key)
		return Bsearch(array , lb , mid , key);
	else
		return Bsearch(array , mid + 1 , ub , key);
}
int main()
{
	int n , L[2000] , i , j , X , ans;
	
	while(scanf("%d" , &n) != EOF)
	{
		if(n == 0)
			break;
		for(i=0 ; i<n ; i++)
		{
			scanf("%d" , &L[i]);
		}
		mergeSort(L , 0 , n-1);
		ans = 0;
		for(i=0 ; i<n-2 ; i++)
		{
			for(j=i+1 ; j<n-1 ; j++ )
			{
				X = Bsearch(L , j+1 , n-1 , L[i] + L[j]);
				if(L[X] > L[i] + L[j])
				{
					ans += n -X;
				}
			}
		}
		printf("%d\n" , ans);
	}
	
	return 0;
}
