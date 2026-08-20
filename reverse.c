#include <stdio.h>
#include <string.h>

void reverseString(char *str) {
int left = 0;
int right = strlen(str) - 1;
char temp;

while (left < right) {
temp = str[left];
str[left] = str[right];
str[right] = temp;

++left;
--right;
}


}

int main() {
char str[99];
printf("Enter an input: ");
scanf("%s", &str);
printf("Original: %s\n", str);
reverseString(str);
printf("Reversed: %s\n", str);
}

