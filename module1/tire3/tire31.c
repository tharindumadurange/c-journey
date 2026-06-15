
//Tire 3 - 3.1 -Sum of digits
#include <stdio.h>

int main(void){
    char line[64];
    int n;
    int sum = 0;

    printf("Enter the positive integer value\n");
    
    // Handle Non numeric garbage
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
        sum += n % 10;
        n /= 10;
    }

    printf("Sum of digits = %d\n", sum);
    return 0;
    
}