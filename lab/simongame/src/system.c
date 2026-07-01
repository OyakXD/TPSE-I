#include "system.h"
#include "hw_types.h"
#include "soc_AM335x.h"
#include "gpio.h"
#include "timer.h"
#include "uart.h"
#include "interrupt.h"
#include "utils.h"

#define CONF_GPMC_CLK           0x88C
#define CONF_GPMC_A5            0x854
#define CONF_GPMC_AD12          0x830
#define CONF_GPMC_BEN1          0x878
#define CONF_GPMC_A0            0x840
#define CONF_GPMC_OEn_REn       0x894
#define CONF_GPMC_WEN           0x898
#define CONF_GPMC_ADVN_ALE      0x890
#define CONF_GPMC_A1            0x844
#define GPIO_IRQSTATUS_0        0x2C

// =============================================================================
//                      PRIVATE FUNCTIONS PROTOTYPES
// =============================================================================

void disableWatchDogTimer(void);
void systemInit(void);

// =============================================================================

// =============================================================================
//                      PUBLIC FUNCTIONS IMPLEMENTATIONS
// =============================================================================

void systemInit(void)
{
    enableClockGPIOx(1);
    enableClockGPIOx(2);

    enableClockDMTIMERx(2);
    enableClockDMTIMERx(7);

    timerInit();

    /* Cronometro */
    DMTimerEnable(SOC_DMTIMER_2_REGS);
    
    intAINTCInit();
    gpioInterruptInit();
    dmTimerInit();
    
    /* PINMUX DOS BOTÕES INPUT_PULL INTERNO */
    HWREG(SOC_CONTROL_REGS + CONF_GPMC_BEN1) |= 0x37; // GPIO1_28
    HWREG(SOC_CONTROL_REGS + CONF_GPMC_A0)   |= 0x37; // GPIO1_16
    HWREG(SOC_CONTROL_REGS + CONF_GPMC_AD12) |= 0x37; // GPIO1_12
    HWREG(SOC_CONTROL_REGS + CONF_GPMC_A1)   |= 0x37; // GPIO1_17
    /*---------------------------------------------------------*/

    /*              PINMUX LEDS                         */
    setPinMuxGPIO(CONF_GPMC_ADVN_ALE);
    setPinMuxGPIO(CONF_GPMC_CLK);
    setPinMuxGPIO(CONF_GPMC_WEN);
    setPinMuxGPIO(CONF_GPMC_OEn_REn);
    /*----------------------------------------------*/

    setupLeds();
    disableWatchDogTimer();
    //infoGame();

}

void disableWatchDogTimer()
{
    HWREG(SOC_WDT_1_WSPR) = 0xAAAA;
    while(HWREG(SOC_WDT_1_WWPS) & (1 << 4));
    HWREG(SOC_WDT_1_WSPR) = 0x5555;
    while(HWREG(SOC_WDT_1_WWPS) & (1 << 4));
}

// =============================================================================