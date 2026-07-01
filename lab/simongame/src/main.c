#include "soc_AM335x.h"
#include "hw_types.h"
#include "system.h"
#include "gpio.h"
#include "uart.h"
#include "timer.h"
#include "utils.h"
#include "interrupt.h"
#include <stdbool.h>
#define TIMER_1MS_COUNT                24000

/* VARIÁVEIS IMPORTANTE PARA O JOGO */
extern unsigned int roundsToWin;
extern unsigned int buttonSequence[];
extern unsigned int pressedButton;
extern unsigned int roundCounter;
extern volatile bool gameStarted;

unsigned int timeLimitTicks = 2000 * TIMER_1MS_COUNT;
unsigned int startTimeTicks = 0;
/* ------------------------------------*/

int main(){

    systemInit();
    gameStarted = false;
    while(1) 
    {
        if(gameStarted == false)  
        {
            startSequence();
            roundCounter = 0;
            DelayMSINT(1500);
            gameStarted = true;
        }

        for (int i = 0; i <= roundCounter; i++) 
        {
            flashLED(buttonSequence[i]);
            DelayMSINT(500);
            allLedOff();
            DelayMSINT(200);
        }

        for (int i = 0; i <= roundCounter; i++) 
        {
            startTimeTicks = DMTimerCounterGet(SOC_DMTIMER_2_REGS);

            while (1) 
            {
                pressedButton = buttonCheck();

                if (pressedButton < 4) 
                {
                    flashLED(pressedButton);

                    if (pressedButton == buttonSequence[i]) 
                    {
                        DelayMSINT(250);
                        allLedOff();
                        DelayMSINT(50);
                        break;
                    } else {
                        loseSequence();
                        break;
                    }
                } else {
                    allLedOff();
                }

                unsigned int currentTicks = DMTimerCounterGet(SOC_DMTIMER_2_REGS);
                if((currentTicks - startTimeTicks) > timeLimitTicks) 
                {
                    loseSequence();
                    break;
                }
            }
            
            if (gameStarted == false) break;
        }

        if (gameStarted == true) 
        {
            roundCounter++;
            if (roundCounter >= roundsToWin) 
            {
                winSequence();
            }
            DelayMSINT(500);
        }
    }
    return 0;
}