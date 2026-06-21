// Tier 3, Task 3.5 - Hex dump of a single byte

# include <stdio.h>

int main(void){
    char line[64];
    int n;
    //int out;

    printf("Enter an integer (0-255)\n");

    // No input (EOF or read error)
    if(fgets(line, sizeof line, stdin) == NULL){
        return 1;
    }

    // Not a number at all
    if(sscanf(line, "%d", &n) != 1){
        printf("Not an integer\n");
        return 1;
    }

    //Reject if out of the range (0-255)
    if ((n < 0) || (n > 255)){
        printf("%d is out of range\n", n);
        return 1;
    }

    printf("%d 0x%02X ", n, (unsigned)n);

    for(int i=7; i>=0; i--){
        //out = (n & (1U<<i)) && 1;
        //printf("%d", out);
        printf("%d", (n >> i) & 1);
    }
    printf("\n");
    return 0;
}
