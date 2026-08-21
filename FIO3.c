#include <stdio.h>

int main() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // 1. The Lookup Table: 256 slots for all possible ASCII characters, initialized to 0
    int freq[256] = {0}; 
    
    // 2. Must be an 'int' (not char) to safely catch the EOF (-1) signal
    int c; 

    // 3. fgetc() grabs a single character at a time until End Of File
    while ((c = fgetc(file)) != EOF) {
        // The character's raw binary value becomes the index
        freq[c]++; 
    }

    fclose(file);

    // 4. Print results (Indices 32 to 126 cover all standard printable characters)
    for (int i = 32; i < 127; ++i) {
        if (freq[i] > 0) {
            printf("'%c' : %d\n", i, freq[i]);
        }
    }

    return 0;
}