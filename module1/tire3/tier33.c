//Tier 3 - 3.3 - Count down with a twist
#include <stdio.h>

int main(void){
    char line[64];
    int n;

    printf("Enter the integer value (1-50)\n");
    
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

    //Reject if out of the range (1-50)
    if ((n < 1) || (n > 50)){
        printf("%d is out of range\n", n);
        return 1;
    }

    while (n > 0){
        if (n % 3 == 0){
            if(n % 5 == 0){
                printf("fizzbuzz\n");
            }
            else{
                printf("fizz\n");
            }
        }
        else if (n % 5 == 0){
            printf("buzz\n");
        }
        else{
            printf("%d\n", n);
        }

        n--;

    };

    return 0;
}