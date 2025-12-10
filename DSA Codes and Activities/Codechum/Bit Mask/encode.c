#include<stdio.h>
#include<stdlib.h>
#include"encode.h"

// Write your functions here...
int* encodeString(char string[]) {
    int *binary = (int*)malloc(64 * sizeof(int));
    
    for(int i = 0; i < 8; i++) {
        unsigned char c = string[i];
        for(int bit = 0; bit < 8; bit++) {
            // Get bit (7-bit) for the first bit, (6-bit) for second, etc.
            // So bit 0 gets MSB, bit 7 gets LSB
            binary[i * 8 + bit] = (c >> (7 - bit)) & 1;
        }
    }
    
    return binary;
}

short int* arrayToBitmask(int arr[]) {
    // Allocate memory for 4 short integers
    short int *result = (short int*)malloc(4 * sizeof(short int));
    
    for(int i = 0; i < 4; i++) {
        short int value = 0;
        // Convert each group of 16 bits to a short integer
        for(int j = 0; j < 16; j++) {
            value = (value << 1) | arr[i * 16 + j];
        }
        result[i] = value;
    }
    
    return result;
}

void displayBitPattern(int arr[]){
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            printf("%d", arr[i * 8 + j]);
        }
        if(i < 7) {
            printf(" ");
        }
    }
}