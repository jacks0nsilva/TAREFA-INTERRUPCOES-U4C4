#include <stdio.h>
#include "pico/stdlib.h"
#include "libs/gpio_config.h"


// Inicializa um pino GPIO (Número do pino | 0: Entrada, 1: Saída)
void initGPIO(uint gpio, bool out){
    gpio_init(gpio);
    gpio_set_dir(gpio, out);
}