#include "system.h"
#include "hw_types.h"
#include "soc_AM335x.h"

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
    disableWatchDogTimer();
}

void disableWatchDogTimer()
{
    HWREG(SOC_WDT_1_WSPR) = 0xAAAA;
    while((HWREG(SOC_WDT_1_WWPS) & (1 << 4)));
    HWREG(SOC_WDT_1_WSPR) = 0x5555;
    while((HWREG(SOC_WDT_1_WWPS) & (1 << 4)));
}

// =============================================================================