#include "system.h"
#include "hw_types.h"
#include "soc_AM335x.h"
#include "gpio.h"
#include "timer.h"
#include "uart.h"
#define CONF_GPMC_CLK           0x88C
#define CONF_GPMC_A5            0x854
#define CONF_GPMC_AD12          0x830

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
    //enableClockGPIOx(2);
    //enableClockGPIOx(3);
    enableClockDMTIMERx(7);

    timerInit();

    //setPinMuxGPIO(CONF_GPMC_A5);
    //setPinMuxGPIO(CONF_GPMC_CLK);
    setPinMuxGPIO(CONF_GPMC_AD12);

    //setOEDirection(1,21,0);
    //setOEDirection(1,22,0);
    //setOEDirection(1,23,0);
    //setOEDirection(1,24,0);
    //setOEDirection(2,1,0);
    setOEDirection(1,12,0);

    disableWatchDogTimer();

    //printMenu();
}

void disableWatchDogTimer()
{
    HWREG(SOC_WDT_1_WSPR) = 0xAAAA;
    while(HWREG(SOC_WDT_1_WWPS) & (1 << 4));
    HWREG(SOC_WDT_1_WSPR) = 0x5555;
    while(HWREG(SOC_WDT_1_WWPS) & (1 << 4));
}

// =============================================================================