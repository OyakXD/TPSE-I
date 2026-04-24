#include <stdio.h>
#include <stdlib.h>

/*
    Original code:
#define DIE \
        fprintf(stderr, "Fatal Error:Abort\n");exit(8); 

int main() {
    / a random value for testing /
    int value;
    value = 1;

    if (value < 0) DIE;
    
    printf("We did not die\n");
    return (0);
}
*/

/* the answer: 
    If value is positive: The if statement skips the fprintf, 
    but the program continues to the next line of execution, 
    which is exit(8). That's why it always terminates.

    Using do/while(0) ensures that the macro behaves as a single instruction.
*/


#define DIE \
    do{ \
        fprintf(stderr, "Fatal Error:Abort\n"); \
        exit(8); \
    } while (0) /* Correct code */

int main() {
    /* a random value for testing */
    int value;
    value = 1;

    if (value < 0) DIE;
    
    printf("We did not die\n");
    return (0);
}
