#include <stdio.h>
int main() {

int n, i;
unsigned long long factorial = 1;
printf("Enter an integer: ");
scanf("%d", &n); 		// storing the input of the user in the variable n

// Error check 1: If user enters an invalid input
if (n < 0) {
printf("Error! The factorial of a negative number does not exist."); }
else {
for (i = 1; i <= n; ++i) {
factorial *= i;			// We're iterating across every integer until n and multiplying it w/ n
}
printf("The factorial of %d = %llu", n, factorial);
} 

}