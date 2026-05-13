# include <stdio.h>

int main(){
    int a = 7;
    int b = 2;
    double c = 7.0;
    double d = 2.0;

    printf("a/b = %d\n",a/b);
    printf("c/d = %f\n",c/d);
    return 0;
// Dividing two integers truncates the decimal part, but division with doubles does not truncate the decimal part.
}