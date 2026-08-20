#include <stdio.h>
#include <stdlib.h>
int main() {
int n, i;
printf("Enter the Fibonacci term: ");
scanf("%d",&n);			// n is the input we expect, which is the Fibonacci term

// Error check
if (n < 0) { printf("Error! You cannot have a negative term for the Fibonacci sequence."); }
else {
// dynamic array memory allocation
int *fib = (int *)malloc(n * sizeof(int));
if (fib == NULL) {
printf("Memory allocation failed!\n");
return 1;
}
fib[0] = 0;
fib[1] = 1;
for (i = 2; i <= n; ++i) {
fib[i] = fib[i-2] + fib[i-1];
}
printf("Fibonacci sequence until term %d is [ ", n);
for (int i = 0; i < n; ++i) {
    printf("%d ", fib[i]); 
}
printf("]");

// Free memory once done
free(fib);
return 0;
}
}