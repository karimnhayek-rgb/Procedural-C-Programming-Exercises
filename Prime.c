#include <stdio.h>
#include <stdbool.h>
int main() {
int i, n;
bool IsPrime;		// true if the number is prime
printf("Enter a number: ");
scanf("%d", &n);
if (n < 0) { n *= -1; } 		// normalize to +ve ints, to satisfy the unsigned logic
if (n == 0) { IsPrime = false; }
if (n == 1) { IsPrime = true; }
for (i = 2; i < n/2; ++i) {
if (n%i == 0) { 
IsPrime = false; 
break; } else {
IsPrime = true;
}
} 

if (IsPrime == true) { printf("The number %d is prime", n); }
else if (IsPrime == false) { printf("The number %d is not prime", n); }

}