// Use bubble sort to sort an array of integers input by user

#include <stdio.h>
#include <stdlib.h>
void bubbleSort(int *arr, int size) {
int len = size;
for (int i = 0; i<len; ++i) {
for (int j = 0; j<len-i-1; ++j) {
if (arr[j+1] < arr[j]) {
int temp = arr[j+1];
arr[j+1] = arr[j];
arr[j] = temp;
}
}
}
}

int main() {
printf("Enter 5 integers:\n");
int *arr = (int*)malloc(5*sizeof(int));
for (int i=0; i<5; ++i) {
scanf("%d",&arr[i]); 
}
int size= 5;
bubbleSort(arr,size);
printf("The sorted array is:\n");
printf("[ ");
for (int j=0; j<5; ++j){
printf("%d ",arr[j]);
}
printf("]");

free(arr); // Because we dynamically allocated memory on the heap using malloc, we must manually release it using free(arr). Strict C best practice to prevent memory leaks in larger, continuous applications.
}
