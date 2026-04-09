#include <stdio.h>
/*
 Original define:
 #define RECIPROCAL (number) (1.0 / (number))

*/

#define RECIPROCAL(number) (1.0 / (number)) // A parameter for the function scope was not defined.
int main() {
    float counter; /* Counter for our table */
    for (counter = 1.0; counter < 10.0;counter += 1.0) {
        printf("1/%f = %f\n", counter, RECIPROCAL(counter));
    }
    return (0);
}