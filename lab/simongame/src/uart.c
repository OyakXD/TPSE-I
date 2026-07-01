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
void infoGame(void);

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

/*
void printMenu(void)
{
    printS("------  MENU TEMPO -----\n\r", 28);
    printS("DIGITE O TEMPO EM SEGUNDOS: ", 28);
}
*/

void infoGame(void)
{
    /* Fonte: https://pt.wikipedia.org/wiki/Genius_(jogo) */

    // Título principal
    printS((unsigned char *)"=========================================\n", 42);
    printS((unsigned char *)"        BEM-VINDO AO JOGO GENIUS         \n", 42);
    printS((unsigned char *)"=========================================\n\n", 43);

    // O que é/História
    printS((unsigned char *)"SOBRE O BRINQUEDO:\n", 19);
    printS((unsigned char *)"Genius era um brinquedo muito popular na\n", 41);
    printS((unsigned char *)"decada de 1980, distribuido no Brasil\n", 39);
    printS((unsigned char *)"pela Brinquedos Estrela.\n\n", 26);

    // Objetivo e Funcionamento
    printS((unsigned char *)"OBJETIVO DO JOGO:\n", 18);
    printS((unsigned char *)"O jogo busca estimular a memorizacao de\n", 40);
    printS((unsigned char *)"cores. Com um formato semelhante\n", 34);
    printS((unsigned char *)"a um OVNI, possui botoes coloridos que\n", 39);
    printS((unsigned char *)"se iluminam\n", 13);
    printS((unsigned char *)"em sequencia.\n\n", 15);

    printS((unsigned char *)"=========================================\n", 42);
    printS((unsigned char *)"   PREPARE SEUS REFLEXOS... INICIANDO!   \n", 42);
    printS((unsigned char *)"=========================================\n", 42);
}
// =============================================================================