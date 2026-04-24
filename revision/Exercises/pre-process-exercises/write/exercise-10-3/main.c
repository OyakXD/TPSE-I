#include <stdio.h>
#define isHex(x) (((x) >= '0' && (x) <= '9') || ((x) >= 'A' && (x) <= 'F') || ((x) >= 'a' && (x) <= 'f'))

int main(){

    isHex(65) ? printf("True\n") : printf("False\n");
    
}