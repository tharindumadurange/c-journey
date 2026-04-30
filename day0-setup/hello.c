#include <stdio.h>
#include <stdint.h>

int main(void) {
    printf("Hello from WSL2 Ubuntu!\n");
    
    uint8_t  byte_var  = 255;
    uint16_t word_var  = 65535;
    uint32_t dword_var = 4294967295;
    
    printf("uint8_t  is %zu byte,  max value %u\n",  sizeof(byte_var),  byte_var);
    printf("uint16_t is %zu bytes, max value %u\n",  sizeof(word_var),  word_var);
    printf("uint32_t is %zu bytes, max value %u\n",  sizeof(dword_var), dword_var);
    
    return 0;
}