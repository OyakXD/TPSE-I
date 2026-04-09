#include <stdio.h>

#define SWAP(x,y) \
    do {auto _tmp = (x); (x) = (y); (y) = _tmp;} \
    while(0)

int main(int argc, char *argv[]){

    int a,b;
    scanf("%d %d", &a, &b);

    SWAP(a,b);

    printf("%d, %d", a,b);

}