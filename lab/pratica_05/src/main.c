#include "soc_AM335x.h"
#include "hw_types.h"
#include "system.h"
#include "gpio.h"
#include "uart.h"
#include "timer.h"
#include "interrupt.h"
#include <stdbool.h>

extern volatile bool flag_gpio;
extern volatile bool flag_gpio2;

#define GPIO_SETDATAOUT                0x194
#define GPIO_CLEARDATAOUT              0x190


int main(){

    unsigned int sequencia_led = 0;
    unsigned int sequencia_frequencia = 0;

    systemInit();
    
    while(1)
    {
        if(flag_gpio == false)
        {   
            sequencia_led++;
            if(sequencia_led > 2)
            {
                sequencia_led = 0;
            }
            flag_gpio = true;
        }

        if(flag_gpio2 == false)
        {
        sequencia_frequencia++;
        if (sequencia_frequencia > 1) 
        {
            sequencia_frequencia = 0;
        }
            flag_gpio2 = true;
        }

        switch(sequencia_led)
        {
            case 0:
                for(int i = 21; i < 25; i++)
                {
                    HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) |= (1 << i);
                }
                break;
            case 1:
                switch (sequencia_frequencia)
                {
                case 0:
                    for(int i =21; i < 25; i++)
                    {
                    HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << i);
                    DelayMSINT(500); 
                    HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << i);
                    DelayMSINT(500);  
                    } 
                    break;
                case 1:
                    for(int i =21; i < 25; i++)
                    {
                    HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << i);
                    DelaySINT(1); 
                    HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << i);
                    DelaySINT(1);  
                    }
                default:
                    break;
                }
                break;
            case 2:
                switch (sequencia_frequencia)
                {
                case 0:
                    for(int i =24; i > 20; i--)
                    {
                        HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << i);
                        DelayMSINT(500); 
                        HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << i);
                        DelayMSINT(500);  
                    } 
                    break;
                case 1:
                    for(int i =24; i > 20; i--)
                    {
                        HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << i);
                        DelaySINT(1); 
                        HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << i);
                        DelaySINT(1);  
                    }
                default:
                    break;
                }
                break;
        }
    }
    
}