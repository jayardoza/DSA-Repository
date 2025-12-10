#include <stdio.h>
#include <ctype.h>
#include <string.h>

// 1. Hash returns a digit in its hundredths place
int hash_hundredths_place(int number) {
    // Extract the hundredths digit (third digit from right)
    return (number / 100) % 10;
}

// 2. Hash accepts a last name and returns 0 if A, 1 if B, ..., 25 if Z
int hash_last_name(const char *lname) {
    if (lname == NULL || strlen(lname) == 0) {
        return -1; // Invalid input
    }
    
    char fchar = toupper(lname[0]);
    if (fchar < 'A' || fchar > 'Z') {
        return -1; // Not a letter
    }
    
    return f - 'A';
}

// 3. Hash accepts an RGB value and returns a digit constrained to 64 palette size
int hash_rgb_to_64_palette(int red, int green, int blue) {
    
    int r_bits = (red >> 6) & 0x03;
    int g_bits = (green >> 6) & 0x03;
    int b_bits = (blue >> 6) & 0x03;
    
    return (r_bits << 4) | (g_bits << 2) | b_bits;
}


int hash_rgb_simple(int red, int green, int blue) {
    int average = (red + green + blue) / 3;
    return average % 64;
}

int main() {
    printf("HASH FUNCTION DEMONSTRATIONS\n\n");
    
    // Test 1: Hundredths place hash
    printf("1. Hundredths Place Hash:\n");
    int test_numbers[] = {1234, 567, 89012, 345, 6789};
    for (int i = 0; i < 5; i++) {
        printf("   hash_hundredths_place(%d) = %d\n", 
               test_numbers[i], hash_hundredths_place(test_numbers[i]));
    }
    
    // Test 2: Last name hash
    printf("\n2. Last Name Hash:\n");
    const char *last_names[] = {"Anderson", "Brown", "Zimmer", "smith", "123Invalid"};
    for (int i = 0; i < 5; i++) {
        int result = hash_last_name(last_names[i]);
        printf("   hash_last_name(\"%s\") = %d", last_names[i], result);
        if (result >= 0 && result <= 25) {
            printf(" (Letter '%c')\n", 'A' + result);
        } else {
            printf(" (Invalid input)\n");
        }
    }
    
    // Test 3: RGB to 64 palette hash
    printf("\n3. RGB to 64 Palette Hash:\n");
    int rgb_test_cases[][3] = {
        {255, 0, 0},     // Red
        {0, 255, 0},     // Green  
        {0, 0, 255},     // Blue
        {128, 128, 128}, // Gray
        {255, 255, 0}    // Yellow
    };
    
    for (int i = 0; i < 5; i++) {
        int r = rgb_test_cases[i][0];
        int g = rgb_test_cases[i][1];
        int b = rgb_test_cases[i][2];
        
        int result1 = hash_rgb_to_64_palette(r, g, b);
        int result2 = hash_rgb_simple(r, g, b);
        
        printf("   hash_rgb(%3d, %3d, %3d) = %2d (bit method), %2d (simple method)\n", 
               r, g, b, result1, result2);
    }
    
    return 0;
}