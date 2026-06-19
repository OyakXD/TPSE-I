#include "uart.h"
#include "hw_types.h"
#include "soc_AM335x.h"

#define UART0_THR   0x0
#define UART0_RHR   0x0
#define UART0_LSR   0x14

// =============================================================================
//                      PRIVATE FUNCTIONS PROTOTYPES
// =============================================================================

void putCh ( unsigned char c );
unsigned int printS ( unsigned char *str, unsigned int length );
char getCh(void);
void printMenu(void);

// =============================================================================

// =============================================================================
//                      PUBLIC FUNCTIONS IMPLEMENTATIONS
// =============================================================================


void putCh ( unsigned char c )
{
    // The transmission hold register (TX FIFO) is not empty. DATASHEET UART_0_LSR DESCRIPTION
    while(!(HWREG(SOC_UART_0_REGS + UART0_LSR) & (1<<5)));
    HWREG(SOC_UART_0_REGS + UART0_THR) = c;
}

unsigned int printS ( unsigned char *str, unsigned int length )
{
    for(int i = 0; i < length; i++)
    putCh(str[i]);
    return(length);
}

char getCh(void)
{
    // There is at least one data character in the RX FIFO. DATASHEET UART_0_LSR DESCRIPTION
    while(!(HWREG(SOC_UART_0_REGS + UART0_LSR) & (1 << 0)));
    return HWREG(SOC_UART_0_REGS + UART0_RHR);
}

void printMenu(void)
{
    printS("------  MENU TEMPO -----\n\r", 28);
    printS("DIGITE O TEMPO EM SEGUNDOS: ", 28);
}

// =============================================================================