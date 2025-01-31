#include <stdio.h>
#include "pico/stdlib.h"

#define LED_PIN 13 // Define o pino GPIO do LED vermelho
#define MATRIZ_PIN 7 // Define o pino GPIO da matriz de LEDs
#define BUTTON_A_PIN 5 // Define o pino GPIO do botão A
#define BUTTON_B_PIN 6 // Define o pino GPIO do botão B

// Inicializa um pino GPIO (Número do pino | 0: Entrada, 1: Saída)
void initGPIO(uint gpio, bool out){
    gpio_init(gpio);
    gpio_set_dir(gpio, out);
}