//Use the divide-and-conquer approach to write a recursive program
//that finds the maximum sum in any contiguous sublist of a given list of n real values.
//Analyze your algorithm, and show the results in order function.


//author:https://github.com/ErnestL1n

//reference:Introduction to Algorithms 3rd(The MIT press)

//Final Project:Promblem G-1


#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

//utility function to return maximum
int maximum(int a, int b) {
	return (a > b) ? a : b;
}

int FindMaximum_Crossing_Subarray(int array[], int low, int middle, int high) {
	int leftsum = INT_MIN;
	int sum = 0;
	for (int i = middle;i >= low;i--) {
		sum += array[i];
		if (sum > leftsum)
			leftsum = sum;
	}
	int rightsum = INT_MIN;
	sum = 0;
	for (int i = middle + 1;i <= high;i++) {
		sum += array[i];
		if (sum > rightsum)
			rightsum = sum;
	}
	return maximum(maximum(rightsum, leftsum), rightsum + leftsum);
}

int Find_Maximum_Subarray(int array[], int low, int high) {
	if (low == high)return array[low];

	int middle = (low + high) / 2;

	return maximum(Find_Maximum_Subarray(array, low, middle),
		maximum(Find_Maximum_Subarray(array, middle + 1, high), FindMaximum_Crossing_Subarray(array, low, middle, high)));

}

int main() {
	int array[] = { -12321, 0, 66, -12, 66, 1 };
	int n = sizeof(array) / sizeof(array[0]);

	printf("The array contains elements :(You can set it in the source code by yourself)\n\n[ ");
	for (int i = 0;i < n;i++)printf("%d ", array[i]);

	printf("]\n\n");

	printf("Maximum sum in any contiguous suarray is %d\n", Find_Maximum_Subarray(array, 0, n - 1));

	char option;
	printf("\npress any key to close ");
	scanf_s("%d", &option);

	return 0;

}