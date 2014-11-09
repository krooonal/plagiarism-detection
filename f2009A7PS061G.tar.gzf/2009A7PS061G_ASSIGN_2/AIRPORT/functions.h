#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
//this file contains all functions that are not involved in I/O or are not called directly from a process function, these are
//helper functions that are called by functions that are called by processes
int palindrome(int number){
	int i = 0;
	int j = 0;
	int array[20];
	int flag = 0;
	while(number>0){
			array[i] = number%10;
			number = number/10;
			i++;
		}
		j = i-1;
		i = 0;
		flag = 0;
		while(i<=j){
				if(array[i]!=array[j]){
						flag = 1;
						break;
					}
					i++;
					j--;
			}
			return flag;
}
//returns 0 if not colorful, 1 if it is
int colorful(int number){
		int i = 0;
		int j = 0;
		int k = 0;
		int m = 0;
		int value = 0;
		int array[10] = {0};
		int digits = 0;
		while(number>0){
			array[digits] = number%10;
			for(k = 0;k<digits;k++){
					if(array[k] == array[digits]){
							return 0;
						}
				}
			digits++;
			number = number/10;
			
			}
			
		int colors[digits][digits];
		
		for(i = 0;i<digits;i++){
				for(j = 0;j<digits;j++){
						colors[i][j] = -999;
					}
			}
		for(i = 0;i<digits;i++){
				colors[0][i] = array[i];
			}
		for(i = 1;i<digits;i++){
				for(j = 0;j<digits-i;j++){
						k = 0;
						value = 1;
						while(k<=i){
								value = value*colors[0][j+k];
								k++;
							}
							colors[i][j] = value;
							for(k = 0;k<=i;k++){
									for(m = 0;m<digits;m++){
											if(k != i && m != j){
													if(colors[k][m] == value){
													return 0;
												}
												}
											
										}
								}
								
					}
			}
		
		return 1;
	}
	
//returns 0 if not prime and i if number is prime
int prime(int number){
		int array[11] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
		int i = 0;
		for(i = 0;i<11;i++){
				if(number%array[i]==0 && number>array[i]){
						return 0;
					}
					
			}
			return 1;
	}
