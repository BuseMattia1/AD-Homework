#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Function to find the minimum of three integers
int min(int x, int y, int z) {
    if (x <= y && x <= z)
        return x;
    else if (y <= x && y <= z)
        return y;
    else
        return z;
}

// Function to compute the minimum edit distance between two strings
int minDis(char* s1, char* s2, int n, int m) {
    int *dp1 = (int *)malloc((m + 1) * sizeof(int));
    int *dp2 = (int *)malloc((m + 1) * sizeof(int));

    // Check if memory allocation was successful
    if (!dp1 || !dp2) {
        printf("Memory allocation failed\n");
        return -1;
    }

    // Initialize the first row (base case for empty s1)
    for (int j = 0; j <= m; j++)
        dp1[j] = j;

    // Iterate over each character of s1
    for (int i = 1; i <= n; i++) {
        // Initialize the first column (base case for empty s2)
        dp2[0] = i;

        // Iterate over each character of s2
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1])
                // If characters match, no operation needed
                dp2[j] = dp1[j - 1];
            else
                // If characters don't match, consider all operations and take the minimum
                dp2[j] = 1 + min(dp2[j - 1], dp1[j], dp1[j - 1]);
        }

        // Copy dp2 to dp1 for the next iteration
        for (int j = 0; j <= m; j++)
            dp1[j] = dp2[j];
    }

    // Result is the edit distance for transforming s1 to s2
    int result = dp1[m];

    free(dp1);
    free(dp2);

    return result;
}

// Function to generate a random string of a given length
void generateRandomString(char* str, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length; i++) {
        // Select a random character from the charset
        str[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    // Null-terminate the string
    str[length] = '\0';
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    int n = 100; //Size of the first string
    int m = 100; //size of the second string

    // Allocate memory for the two strings
    char* str1 = (char *)malloc((n + 1) * sizeof(char));
    char* str2 = (char *)malloc((m + 1) * sizeof(char));

    if (!str1 || !str2) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Generate random strings
    generateRandomString(str1, n);
    generateRandomString(str2, m);

    // Print the generated strings (comment out if the size of the string becomes too large)
    printf("String 1: %s\n", str1);
    printf("String 2: %s\n", str2);

    // Compute and print the minimum edit distance between the two strings
    printf("Minimum edit distance: %d\n", minDis(str1, str2, n, m));

    // Free allocated memory for the strings
    free(str1);
    free(str2);

    return 0;
}
