# include <stdio.h>
# include <stdint.h>

int main(void){
    uint8_t reg = 0;
    char line[64];
    int opsel, bitsel;

    printf("Please Select an option\n (1) set bit\n (2) clear bit\n (3) toggle bit\n (4) test bit\n (5) print register\n (6) quit\n");
    
    while(1){
        // No input (EOF or read error)
        if(fgets(line, sizeof line, stdin) == NULL){
            return 0;
        }

        // Not a number at all
        if(sscanf(line, "%d", &opsel) != 1){
            printf("Not an integer, please enter valid menu option\n");
            continue;
        }

        //Reject if out of the range (1-6)
        if ((opsel < 1) || (opsel > 6)){
            printf("%d is out of menu range, enter a value within menu range\n", bitsel);
            continue;
        }

        if(opsel == 5){
            printf("Register value = %u\n", reg);
            printf("Please Select an option\n (1) set bit\n (2) clear bit\n (3) toggle bit\n (4) test bit\n (5) print register\n (6) quit\n");            
            continue;
        }
        
        
        else if(opsel == 6){
            printf("Program Exit\n");
            return 0;
        }
        
        else{
            while(1){
                printf("Please enter the bit number (0-7)\n");
                // No input (EOF or read error)
                if(fgets(line, sizeof line, stdin) == NULL){
                    printf("Read error\n");
                    continue;
                }

                // Not a number at all
                else if(sscanf(line, "%d", &bitsel) != 1){
                    printf("Not an integer\n");
                    continue;
                }

                //Reject if out of the range (1-6)
                else if ((bitsel < 0) || (bitsel > 7)){
                    printf("%d is out of bit range\n", opsel);
                    continue;
                }
                else{
                    break;
                }
            }

            switch(opsel){
                case 1:
                    reg |= 1U << bitsel;
                    printf("%d bit set\n",bitsel);
                    break;
                
                case 2:
                    reg &= ~(1U << bitsel);
                    printf("%d bit cleared\n",bitsel);
                    break;

                case 3:
                    reg ^= 1U << bitsel;
                    printf("%d bit toggled\n",bitsel);
                    break;
                    
                case 4:
                    printf("bit %d = %d\n", bitsel, (reg >> bitsel) & 1);
                    break;
                    
                default:
                    printf("Error..\n");
                    break;
            }
            printf("Please Select an option\n (1) set bit\n (2) clear bit\n (3) toggle bit\n (4) test bit\n (5) print register\n (6) quit\n");
            
        }

    }
    return 0;
}