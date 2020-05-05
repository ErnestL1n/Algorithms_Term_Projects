//Write a program to calculate the Binomial Coefficient  C(n,k)


//author:https://github.com/ErnestL1n

//reference:Introduction to Algorithms 3rd(The MIT press)

//Final Project:Promblem G-2

#include<stdio.h>
#include<stdlib.h>


int minimum(int a, int b) {
	return (a < b) ? a : b;
}

int Binomial_Cofficient(int n,int k) {

	int **BioCof = (int**)calloc((n + 1),sizeof(int*));
	for (int i = 0;i <= n;i++)BioCof[i] = (int*)calloc((k + 1), sizeof(int));

	for(int i=0;i<=n;i++)
		for (int j = 0;j <= minimum(i, k);j++) {
			if (j == 0 || j == i)BioCof[i][j] = 1;

			else {
				BioCof[i][j] = BioCof[i - 1][j] + BioCof[i - 1][j - 1]; 
			}
		}


	return BioCof[n][k];
}

int main() {

	int n = 9,k = 6;

	printf("Binomial Coefficient C(%d, %d)=%d", n, k, Binomial_Cofficient(n, k));
	printf("\n\n");

	return 0;
}