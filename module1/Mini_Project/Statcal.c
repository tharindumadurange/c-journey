#include <stdio.h>

int main(void){
    char line[64];
    double values[100];
    int menuHistory[32];
    double temp;
    int n, menuValue, x, cntAbvMean, overflowflag;
    double min,max,mean,range;
    int i = 0;
    int j = 0;
    int menuCnt = 0;

    printf("== Statistics Calculator ==\n");
    printf("Enter up to 100 numeric measurements: then explore them via the menu\n");
    printf("Please enter number of measurements\n");

    while(1){ // accepting number of values
        
        if(fgets(line, sizeof (line), stdin) == NULL){
           printf("Error, Program Exit\n");
           return 1; 
        }
        
        else if(sscanf(line, "%d", &n) != 1){
            printf("Not an Integer, please try again\n");
            continue;
        }
        
        else if(n<1 || n>100){
            printf("Out of range 1- 100, please try again\n");
            continue;
        }
        
        else{
            break;
        }
    }
    
    printf("Number of values = %d\n", n);
    while(i < n){ // accepting values
            
        printf("value [%d of %d]:", i+1, n);
        
        if(fgets(line, sizeof(line), stdin) == NULL){
        printf("Error, Program Exit\n");
        return 1; 
        }

        else if(sscanf(line, "%lf", &temp) != 1){
            printf("Not an Decimal number, please try again\n");
            continue;
        }

        values[j++] = temp;
        i++;
    }

    printf("------ Menu ------\n1).min     5).count above mean\n2).max     6).print all\n3).mean    7).print history\n4).range   8).quit\n");
    overflowflag = 0;

    while(1){ // menu loop
        
        printf("Please enter a valid menu number\n");
        
        if(fgets(line, sizeof (line), stdin) == NULL){
           printf("Error, Program Exit\n");
           return 1; 
        }
        
        else if(sscanf(line, "%d", &menuValue) != 1){
            printf("Not an Integer, please try again\n");
            continue;
        }
        
        else if(menuValue<1 || menuValue>8){
            printf("Out of menu range (1 - 8), please try again\n");
            continue;
        }
        else{
            printf("Choice %d\n", menuValue);
            menuHistory[menuCnt++] = menuValue;
            max = values[0];
            min = values[0];
            mean = 0;
            cntAbvMean = 0;
            if(menuCnt == 32){
                menuCnt = 0;
                overflowflag++;
            }

            switch(menuValue){
                case 1:
                    for(x = 0; x < n; x++){
                        if (values[x] < min){
                            min = values[x];
                        }
                    }
                    printf("min = %.2lf\n", min);
                    break;

                case 2:
                    for(x = 0; x < n; x++){
                        if (values[x] > max){
                            max = values[x];
                        }
                    }
                    printf("max = %.2lf\n", max);
                    break;
                    
                case 3:
                    for(x = 0; x < n; x++){
                        mean += values[x];
                    }
                    printf("mean = %.2lf\n", mean/n);
                    break;
                
                case 4:
                    for(x = 0; x < n; x++){
                        if(values[x] < min){
                            min = values[x];
                        }
                        if(values[x] > max){
                            max = values[x];
                        }
                    }
                    printf("range = %.2lf\n", range = max - min);       
                    break;

                case 5:
                    for(x = 0; x < n; x++){
                        mean += values[x];
                    }
                    mean /= n;
                    for(x = 0; x < n; x++){
                        if(values[x] > mean){
                            cntAbvMean++;
                        }
                    }
                    printf("Count above mean = %d\n", cntAbvMean);
                    break;

                case 6:
                    for(x = 0; x < n; x++){
                        printf("%.2lf\t", values[x]);
                    }
                    printf("\n");
                    break;

                case 7:
                    if(overflowflag){
                        for(x = 0; x < 32; x++){
                            int slot = (menuCnt + x) % 32;   // start at oldest, wrap around
                            printf("%d\t", menuHistory[slot]);
                        }
                    }
                    else{    
                        for(x = 0; x < menuCnt; x++){
                            printf("%d\t", menuHistory[x]);
                        }
                    }
                    printf("\n");
                    break;

                case 8:
                    printf("Session ended. %d values processed, %d menu action performed\n", n, (overflowflag * 32) + menuCnt);
                    return 0;

                default:
                    break;    
            }
        }        
    }
    return 0;
}


