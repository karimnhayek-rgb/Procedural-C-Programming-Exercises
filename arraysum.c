// 7. Implement a function that takes a pointer to an array and its size, returns the sum

#include <stdio.h>

int arraySum(int *arr, int size) {
int sum = 0;
for (int i = 0; i < size; ++i) {
sum += arr[i];
}
return sum;
}

int main() {

int arr[] = {1,4,5,6,8};
int size = sizeof(arr)/sizeof(arr[0]); // sizeof() returns the total size in bytes. an int is 4 bytes so the loop ran 20 times :D
printf("%d", arraySum(arr, size));
}