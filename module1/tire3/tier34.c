#include <stdio.h>

int main(void) {
    char line[64];
    int n, sum = 0;
    char extra;

    while (1) {
        printf("Enter an integer or 'q' to quit\n");

        if (fgets(line, sizeof line, stdin) == NULL) {
            return 0;                  // no more input -> stop. This is OK.
        }
        if (line[0] == 'q' && (line[1] == '\n' || line[1] == '\0')) {
            return 0;                  // 'q' = normal quit -> success
        }

        if (sscanf(line, "%d %c", &n, &extra) == 1) {
            sum += n;
            printf("sum so far: %d\n", sum);
        } else {
            printf("Not an integer, try again\n");   // show a message
        }
    }
}