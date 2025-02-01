#include <stdio.h>
#include "pico/stdlib.h"


// Inicializa um pino GPIO (Número do pino | 0: Entrada, 1: Saída)
void initGPIO(uint gpio, bool out){
    gpio_init(gpio);
    gpio_set_dir(gpio, out);
}