#include <stdio.h>
#include <stdlib.h>

/*  
PHASE 1: PREPROCESSING PIPELINE

For all filtering functions, the pattern is void filter (float * restrict INPUT, float * restrict OUTPUT, int SIGNAL_SIZE) { ... }

The reason we use restrict is for best practice. The compiler thinks INPUT and OUTPUT might point to the same memory 
location, so every time either argument gets called, it has to re-read it from RAM instead of caching it in a fast CPU register.
This is called pointer aliasing and causes the algorithm to run slowly. Using restrict is a feature in C which allows us to
override the compiler's paranoia.  :) 

  */

// 1. LOWPASS FILTER
void lowpass(float * restrict x, float * restrict y, int x_size) {
/* 
y[n] = 2y[n-1] - y[n-2] + (1/32)(x[n] - 2x[n-6] + x[n-12])

This is the 11Hz lowpass filter expressed in time. It effectively suppresses power-line interference, if present. 
It introduces a delay of 25 ms.
*/

// Initial Conditions
y[0] = (1.0f/32.0f) * x[0];			// We append an f to force purely 32-bit float arithmetic. 
y[1] = (2.0f) * y[0] + (1.0f/32.0f) * x[1];
y[2] = (2.0f) * y[1] - y[0] + (1.0f/32.0f) * x[2];
int n = 3;

while (n < 6) {
y[n] = (2.0f) * y[n-1] - y[n-2] + (1.0f/32.0f) * x[n];
n++;
}

while (n < 12) {
y[n] = (2.0f) * y[n-1] - y[n-2] + (1.0f/32.0f) * (x[n] - (2.0f) * x[n-6]);
n++;
}

for (int n=12;n<x_size;n++) {
y[n] = (2.0f) * y[n-1] - y[n-2] + (1.0f/32.0f) * (x[n] - (2.0f) * x[n-6] + x[n-12]);
}

}


// 2. HIGHPASS
void highpass(float * restrict x, float * restrict y, int x_size) {
/*
 y[n] = x[n-16] - (1/32)(y[n-1] + x[n] - x[n-32])

This is the 5Hz highpass filter and introduces a delay of 80 ms.
*/

// Initial Conditions
y[0] = -(1.0f/32.0f) * x[0];

int n = 1;
while (n < 16) {
y[n] = -(1.0f/32.0f) * (y[n-1] + x[n]);
n++;
}

while (n < 32) {
y[n] = x[n-16] - (1.0f/32.0f) * (y[n-1] + x[n]);
n++;
}

for (int n=32;n<x_size;++n) {
y[n] = x[n-16] - (1.0f/32.0f) * (y[n-1] + x[n] - x[n-32]);
}

}

// 3. DERIVATIVE OPERATOR
void derive(float * restrict x, float * restrict y, int x_size) {
/*
 y[n] = (1/8)(2x[n]+x[n-1]-x[n-3]-2x[n-4])

It approximates the ideal d/dt operator up to 30Hz. The derivative procedure suppresses the low frequency components of 
the P and T waves, and provides a large gain to the HF components from the high slopes of the QRS complex.
*/

// Initial Conditions
y[0] = (1.0f/8.0f) * (2.0f * x[0]);
y[1] = (1.0f/8.0f) * (2.0f * x[1] + x[0]);
y[2] = (1.0f/8.0f) * (2.0f * x[2] + x[1]);
y[3] = (1.0f/8.0f) * (2.0f * x[3] + x[2] - x[0]);

for (int n=4; n<x_size; ++n) {
y[n] = (1.0f/8.0f) * (2.0f * x[n] + x[n-1] - x[n-3] - 2.0f * x[n-4]);
}

}

// 4. SQUARING OPERATION
void square(float * restrict x, float * restrict y, int x_size) {
/*
  The squaring operation makes the result positive and emphasizes large differences resulting from QRS complexes.
The small differences arising from P and T waves are suppressed, while the high-frequency components in the signal 
related to the QRS complex are further enhanced.
*/

for (int i=0; i<x_size; ++i) {
y[i] = x[i] * x[i];
}

}

// 5. MOVING WINDOW INTEGRATOR
void MWI(float * restrict x, float * restrict y, int x_size) {
/*
y[n] = (1/N)*(x[n-(N-1)] + x[n-(N-2)] + ... + x[n])

Window width of N=30 was found to be suitable for a sampling frequency of 200Hz. 
*/
float N = 30.0f; 

for (int n=0; n<x_size; ++n) {
float sum = 0.0f;
for (int i=0; i<(int)N; ++i) {
if (n - i >= 0) { sum += x[n-i)]; }
}
y[n] = (1.0f/N) * (sum);
}

}

/*
PHASE 2: INITIALIZATION

This is the 2-second learning phase of the algorithm.

We need to pass the calculated values back out to our main program, so their arguments must be pointers (float *).
*/

void Initialize(float * restrict x, float * restrict t, float *SPKI, float *NPKI, float *TH1, float *TH2) {
// Search through 2 seconds in for the local peak

int i = 1;
float max_peak = 0.0f;
float noise_sum = 0.0f;
int noise_peak_count = 0;
while (t[i] <= 2.0f) {
if (x[i] > x[i-1] && x[i] > x[i+1]) { 
if (x[i] > max_peak) { max_peak = x[i]; }
}

i++;
*SPKI = max_peak;
}

i = 1;
while (t[i] <= 2.0f) {
if (x[i] > x[i-1] && x[i] > x[i+1]) {
if (x[i] != max_peak) { 
noise_sum += x[i];
noise_peak_count++;
}
}
i++;
}

if (noise_peak_count > 0) {
  *NPKI = noise_sum / (float)noise_peak_count;
} else {
  *NPKI = 0.0f;
}

*TH1 = *NPKI + 0.25f * (*SPKI - *NPKI);
*TH2 = 0.5f * (*TH1);
}

// PHASE 3: DYNAMIC DETECTION ENGINE

void main() {

/ * Filtering test
float x[20] = {
    0.000,  0.951,  0.588, -0.588, -0.951,
    0.000,  0.951,  0.588, -0.588, -0.951,
    0.000,  0.951,  0.588, -0.588, -0.951,
    0.000,  0.951,  0.588, -0.588, -0.951
};

float y1[20];
float y2[20];

int size = 20;

lowpass(x, y1, size);
highpass(y1, y2, size);

for (int i=0; i<20; ++i) {
printf("%f ", y2[i]);
}

*/

}