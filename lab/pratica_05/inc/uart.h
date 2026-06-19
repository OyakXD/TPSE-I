#ifndef UART_H
#define UART_H

/* Função que recebe a entrada do usuário*/
extern void putCh ( unsigned char c );

/* Função que printa uma string*/
extern unsigned int printS ( unsigned char *str, unsigned int length );

/* Função que lê a entrada do usuário*/
extern char getCh(void);

/* Função para printar o menu com algumas informações */
extern void printMenu(void);


#endif // UART_H