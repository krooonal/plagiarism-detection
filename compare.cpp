#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <list>
#include <string>
#include <fstream>


using namespace std;

#define DEBUG 0
#define all(C) (C).begin() , (C).end()
#define tr(C , it) for(typeof((C).begin()) it = (C).begin() ; it != (C).end() ; it++)

#define present(C , key) ((C).find(key) != (C).end())
#define cpresent(C , key) (find(all(C) , key) != (C).end()

#define sz(a) int((a).size())
#define pb push_back

//#define MTHRES 10
//#define SIMTHRES 0.6

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int , int> PI;

double SIMTHRES;
int MTHRES;

/*
Failure Function for KMP algorithm
*/
void preKMP(string pattern, int f[])
{
        int m = pattern.length(),k;
        f[0] = -1;
        for (int i = 1; i<m; i++)
        {
                k = f[i-1];
                while (k>=0)
                {
                        if (pattern[k]==pattern[i-1])
                                break;
                        else
                                k = f[k];
                }
                f[i] = k + 1;
        }
}

/*
Standard KMP algorithm used for string comparision
*/
bool KMP(string target, string pattern)
{ 
        int m = pattern.length();
        int n = target.length();
        int f[m];
         
        preKMP(pattern, f);
         
        int i = 0;
        int k = 0;
         
        while (i<n)
        {
                if (k==-1)
                {
                        i++;
                        k = 0;
                }
                else if (target[i]==pattern[k])
                {
                        i++;
                        k++;
                        if (k==m)
                                return 1;
                }
                else
                        k=f[k];
        }
        return 0;
}

int main(int argc , char *argv[])
{
	if(argc < 3)
	{
		printf("\nwrong format\n");
		return 1;
	}
	//printf("%s %s\n" , argv[1] , argv[2]);
	
	int i , j , size1 , size2 , tmatched;
	string tokens1 , tokens2 , temps;
	ifstream file1 , file2;
	
	file1.open(argv[1]);
	file2.open(argv[2]);
	
	MTHRES = 10;
	if(argc == 4)
	{
		SIMTHRES = atof(argv[3]);
	}
	else
	{
		SIMTHRES = 0.7;
	}
	
	
	file1 >> tokens1;
	file2 >> tokens2;
	
	file1.close();
	file2.close();
	
	//printf("size1 %d size2 %d\n" , tokens1.size() , tokens2.size() ) ;
	size1 = tokens1.size();
	size2 = tokens2.size();
	
	
	VI mtsize(size2+1);
	VI mtkn(size2);
	int largestMatchedT = 0;
	for(i=0 ; i<size2 ; i++)
	{
		if(mtkn[i] == 1)
			continue;
		for(j=MTHRES ; j <= size2-i ; j++)
		{
			if(KMP(tokens1 , tokens2.substr(i , j)) == true)
			{
				mtsize[j]++;
				if(j > largestMatchedT)
					largestMatchedT = j;
				for(int k=i ; k<i+j ; k++)
					mtkn[k] =1;
				
			}
			else
				break;
		}
	}
	
	
	tmatched = 0;
	for(i = 0 ; i < size2 ; i++)
	{
		tmatched += mtkn[i];
	}
	//printf("similarity = %lf tmathced = %d\n" , (double)tmatched / size2 , tmatched);
	
	if((double)tmatched/size2 >= SIMTHRES )
	{
		printf("%s,%s,%lf\n" , argv[1] , argv[2] , (double)tmatched / size2);
		//printf("\n\n\nPotential plagiarism case with similarity : %lf\n\n\n" , (double)tmatched / size2);
	}
	
	
	return 0;
}
