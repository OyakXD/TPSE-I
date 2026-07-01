#include "utils.h"


extern volatile bool flag_gpio; // flag botao1 
extern volatile bool flag_gpio2; // flag botao2
extern volatile bool flag_gpio3; // flag botao3
extern volatile bool flag_gpio4; // flag botao4

// Variável global para guardar o estado do gerador
unsigned int roundsToWin = 10;
unsigned int buttonSequence[16];
unsigned int pressedButton = 4;
unsigned int roundCounter = 1;
volatile bool gameStarted = false;

// =============================================================================
//                      PRIVATE FUNCTIONS PROTOTYPES
// =============================================================================

void startSequence(void);
void winSequence(void);
void loseSequence(void);
int buttonCheck(void);

// =============================================================================

// =============================================================================
//                      PUBLIC FUNCTIONS IMPLEMENTATIONS
// =============================================================================

void startSequence(void)
{
    for(int i = 0; i < roundsToWin; i++) 
    {
        buttonSequence[i] = rand % 4; // Gera um número de 0 a 3
    }

    for (int i = 0; i < 4; i++) 
    {
        flashLED(i);
        DelayMSINT(500);
        allLedOff();
        DelayMSINT(500);
    }
}

void winSequence(void)
{
    for (int j = 0; j < 4; j++) flashLED(j);
    DelayMSINT(2000);

    do {
        pressedButton = buttonCheck();
    } while (pressedButton > 3);
    DelayMSINT(100);

    gameStarted = false;
}

void loseSequence(void)
{
    for (int j = 0; j < 4; j++) flashLED(j);
    DelayMSINT(2000);

    do {
        pressedButton = buttonCheck();
    } while(pressedButton > 3);
    DelayMSINT(200);

    gameStarted = false;
}

int buttonCheck(void)
{
    if(flag_gpio == false) // GPIO1_28 corresponde ao LED[3]
    {
        flag_gpio = true;
        return 3;
    }
    else if (flag_gpio2 == false) // GPIO1_16 corresponde ao LED[1]
    {
        flag_gpio2 = true;
        return 1;
    }
    else if (flag_gpio3 == false) // GPIO1_17 corresponde ao LED[2]
    {
        flag_gpio3 = true;
        return 2;
    }
    else if (flag_gpio4 == false) // GPIO1_12 corresponde ao LED[0]
    {
        flag_gpio4 = true;
        return 0;
    }

    return 4;
}





