#include <stdio.h>

void printBinary(int num) {
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}


int main(){

    int x = 0xF;
    printBinary(x);
    int counter = 0;
    int result = 0;

    for(int i = 0; i < 32; i++){

        if(x & 1) {
            counter++;
        }

        x >>= i;
    }
    
    for(int i = 0; i < counter; i++){
        result |= (1 << (31 - i)); 
    }                                 

    printBinary(result);
}