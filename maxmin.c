// 5. Find the min, max, and average of an array of integers

#include <stdio.h>
#include <stdlib.h>

int main() {
int arr[100]; 		// Accepting upto 100 integer input
int max, min, num;
float average;

printf("Enter how many integers you have: ");
scanf("%d", &num);

printf("Now write down those numbers: ");
for (int i=0; i<num; ++i) { scanf("%d",&arr[i]); }

max = arr[num-1];
min = arr[0];
float sum = 0.0;
for (int j=0; j<num; ++j) {
if (arr[j] > max) { max = arr[j]; }
if (arr[j] < min) { min = arr[j]; }
sum += arr[j];
}
average = sum / num;
printf("The maximum is %d, the minimum %d, and the average %f", max, min, average);
}