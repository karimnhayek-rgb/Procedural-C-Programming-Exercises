// 15. Implement a simple peak detector: find all local maxima in an array of floats

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void peak_finder(float *arr, float *t_idx, float *peaks, float *p_tidx, int window_size, int arr_size) {
// peak finder engine
int tries = ceil((float)arr_size / window_size);
int index = 0;
for (int i=0; i<tries; ++i) {
int count = index;
float max = 0;
float max_idx = 0;
while (count < (window_size + index) && count < arr_size) {
if (arr[count] > max) { max = arr[count]; 
		  max_idx = t_idx[count]; }
count++;
} 
peaks[i] = max;
p_tidx[i] = max_idx;
index += window_size;
}

}

void main() {

float arr[13] = {0.1, 1.2, 3.4, 2.2, 1.3, 1.25, 3.2, 1.25, 1.0, 1.2, 3.3, 3.0, 1.01};
float tidx[13] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.2, 1.3};
int w = 5;
int arr_size = 13;
int num = ceil((float)arr_size/w);
float peaks[num];
float peak_idx[num];
peak_finder(arr, tidx, peaks, peak_idx, w, arr_size);

printf("The peaks and their time locations are ");
for (int i=0; i<num; ++i) {
printf("%f @ %f | ", peaks[i], peak_idx[i]);
}

}