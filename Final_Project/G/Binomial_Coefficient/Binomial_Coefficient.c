//Write a program to calculate the Binomial Coefficient  C(n,k)


//author:https://github.com/ErnestL1n

//reference:Introduction to Algorithms 3rd(The MIT press)

//Final Project:Promblem G-2

#include<stdio.h>
#include<stdlib.h>


int minimum(int a, int b) {
	return (a < b) ? a : b;
}

int Binomial_Cofficient(int n, int k) {

	int** BioCof = (int**)calloc((n + 1), sizeof(int*));
	for (int i = 0;i <= n;i++)BioCof[i] = (int*)calloc((k + 1), sizeof(int));

	for (int i = 0;i <= n;i++)
		for (int j = 0;j <= minimum(i, k);j++) {
			if (j == 0 || j == i)BioCof[i][j] = 1;

			else {
				BioCof[i][j] = BioCof[i - 1][j] + BioCof[i - 1][j - 1];
			}
		}


	return BioCof[n][k];
}


int main() {

	int n, k;
	printf("Enter Binomial Coefficient (n>=k)\n\n");
	printf("n= ");
	scanf_s("%d", &n);
	printf("k= ");
	scanf_s("%d", &k);

	printf("\nBinomial Coefficient C(%d, %d)=%d", n, k, Binomial_Cofficient(n, k));
	printf("\n\n");

	char option;
	printf("\npress any key to close ");
	scanf_s("%d", &option);
	return 0;
}