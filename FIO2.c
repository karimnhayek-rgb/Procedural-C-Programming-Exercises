#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {

FILE *file = fopen("Nums.csv", "r");
if (file == NULL) {
printf("The file is empty");
}

char buffer[256];
int numbers[5];
int i=0;
while(fgets(buffer, sizeof(buffer), file)) {
char *token = strtok(buffer, ",");
while (token != NULL && i<5) {
numbers[i] = atoi(token);
token = strtok(NULL, ",");
i++;
}
}
int sum = 0;
float avg;
for (int i=0; i<5; ++i) {
sum += numbers[i];
}
avg = sum/5.0;
printf("The computed average in this file is equal to %f",avg);

fclose(file);

}