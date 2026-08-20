// Take two sorted, and merge sort them together
#include <stdio.h>
#include <stdlib.h>
int* mergeSort(int *arr1, int size1, int *arr2, int size2) {
int totalSize = size1 + size2;
int *arr3 = (int*)malloc(totalSize*sizeof(int));

int i = 0;
int j = 0;
int k = 0;

while (i < size1 && j < size2) {
if (arr1[i] < arr2[j]) {
arr3[k] = arr1[i];
i++;
} else {
arr3[k] = arr2[j];
j++;
}
k++;
}

while (i < size1) {
arr3[k] = arr1[i];
k++;
i++;
}

while (j < size2) {
arr3[k] = arr2[j];
k++;
j++;
}

return arr3;

}

int main() {
int sorted_array1[3] = {2, 5, 8};
int sorted_array2[4] = {1, 4, 6, 9};
int size1 = 3;
int size2 = 4;
int totalSize = size1 + size2;
printf("The merge sorted array is:\n ");
printf("[ ");
int *arr = mergeSort(sorted_array1, size1, sorted_array2, size2);
for (int i=0; i<totalSize; ++i){
printf("%d ", arr[i]);
}
printf("]");
}