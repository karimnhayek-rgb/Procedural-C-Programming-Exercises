// 14. Implement numerical differentiation

#include <stdio.h>
#include <stdlib.h>

void diff(float *arr, float *time_index, float *out, int array_size) {
for (int i=1;i<array_size;++i) {
out[i-1] = (arr[i] - arr[i-1]) / (time_index[i] - time_index[i-1]);
}
}

void main() {
// Initialization of the arrays
float arr[5] = {1.2, 2.3, 3.1, 1.89, 0.87};
float t_idx[5] = {0.04, 0.2, 0.26, 0.3, 0.37};
float out[4];
diff(arr, t_idx, out, 5);
printf("The (backward) difference of the numerical sequence is [ ");

for (int i=0; i<4;++i) {
printf("%f ", out[i]);
}
printf("]");

}