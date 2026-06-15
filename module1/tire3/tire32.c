//Tier 3 - 3.2 -Reverse the digits
#include <stdio.h>
#include <limits.h> 

int main(void){
    char line[64];
    int n, digit;
    int reversed = 0;

    printf("Enter the non-negative integer value\n");
    
    // No input (EOF or read error)
    if(fgets(line, sizeof line, stdin) == NULL){
        return 1;
    }

    // Not a number at all
    if(sscanf(line, "%d", &n) != 1){
        printf("Not an integer\n");
        return 1;
    }

    // Handling Negative integers
    if (n<0){
        printf("Please enter a non-negative integer\n");
        return 1;
    }

    while (n > 0){
        digit = n % 10;
        n /= 10;
        if (reversed > (INT_MAX - digit) / 10) {
        printf("Reversed value overflows int\n");
        return 1;
        }
        reversed = reversed * 10 + digit;
    }

    printf("Reversed digits = %d\n", reversed);
    return 0;
    
}