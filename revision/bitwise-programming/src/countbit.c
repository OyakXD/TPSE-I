#include <stdio.h>
#include <stdlib.h>
#define IS_SET    0x1

void printBinary(int num) {
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}


int main(){

    int a = 5;
    int counter = 0;
    printBinary(a);

    for(int i = 0; i < 32; i++ ){
        if(a & IS_SET)
            counter++;

        a = a >> i;
    }

    printf("%d\n", counter);
}