#ifndef GPIO_H
#define GPIO_H


// Função para ativar o clock de um GPIO x [1..3]
extern void enableClockGPIOx(volatile unsigned int gpio_number);

// Função que faz a multiplexação do pino para IO
extern void setPinMuxGPIO(volatile unsigned int pinName);

/* Função que determina se o pino de GPIO que corresponde ao numero gpio_number,
   no registrador reg_gpio, na direção direction é 0(Saída) ou 1(Entrada) 
*/
extern void setOEDirection(volatile unsigned int gpio_number, volatile unsigned int reg_gpio ,volatile unsigned int direction);

// Função que verifica se o clock do GPIO está ativado.
extern void verifyStatusClockGPIOx(volatile unsigned int gpio_number);

#endif