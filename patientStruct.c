#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[99];
	int age;
	int heart_rate;
} Patient;

void main() {
Patient *patient[5];
char patient_name[5][20] = {"Patrick", "Giuseppe", "Martini", "Giorgio", "Alicia"};
int patient_age[5] = {23, 26, 32, 45, 55};
int patient_hr[5] = {120, 90, 130, 160, 100};

for (int i = 0; i<5; ++i) {
	patient[i] = malloc(sizeof(Patient));
	strcpy(patient[i]->name, patient_name[i]);
	patient[i]->age = patient_age[i];
	patient[i]->heart_rate = patient_hr[i];
}
int max = 0;
int index;
for (int j = 0; j<5; ++j) {
	if (patient[j]->heart_rate > max) { max = patient[j]->heart_rate;
				     index = j; }
}

printf("The patient with the highest heart rate is %s", patient[index]->name);

for (int k=0; k<5; ++k) {
free(patient[k]);
}
}