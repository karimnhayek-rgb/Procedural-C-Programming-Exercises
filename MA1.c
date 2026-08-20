// 13. Implement a moving average filter on an array of floats

#include <stdio.h>
#include <stdlib.h>

// Building the engine: the MA filter
void MA_filter(float *arr, float *out, int array_size, float window_size) {
for (int n=0; n< array_size; ++n) {
float sum = 0.0;
for (int k=0; k<window_size;++k) {
if (n >= k) { sum += arr[n-k]; }
}
out[n] = (1/window_size) * (sum);
}
}

void main() {
// Initialization of the array of floats
float arr[5] = {1.2, 2.3, 3.1, 1.89, 0.87};
float out[5];
MA_filter(arr, out, 5, 5.0);

printf("The moving average filtered result is [ ");
for (int i=0; i<5; ++i) {
printf("%f ", out[i]);
}
printf("]");

}