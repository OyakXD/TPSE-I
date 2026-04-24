#include <stdio.h>
#include <stdlib.h>


int main(){
    
    __uint32_t a = 0x00010005;

    __uint32_t splits[8];

    for(int i = 0; i < 8 ; i++) {
        splits[i] = (a >> (i * 4)) & 0xF;
    }

    for(int i = 0; i < 8; i++) {
        printf("splits[%d] = %u\n", i, splits[i]);
    }

    

    /* code test*/
    /*
    __uint8_t a = 5;

    __uint8_t split1 = (a >> 4) & 0xF;
    __uint8_t split2 = (a & 0xF);

    printf("original: %d, split1: %d, split2: %d\n", a, split1, split2);
    */
}