#include <stdio.h>

int main (){
    printf("Size of char is %zu byte\n",sizeof(char));
    printf("Size of short is %zu bytes\n",sizeof(short));
    printf("Size of int is %zu bytes\n",sizeof(int));
    printf("Size of long is %zu bytes\n",sizeof(long));
    printf("Size of long long is %zu bytes\n",sizeof(long long));
    printf("Size of float is %zu bytes\n",sizeof(float));
    printf("Size of double is %zu bytes\n",sizeof(double));
    return 0;
}