#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "pio_config.h"


#define LED_PIN 13 // Define o pino GPIO do LED vermelho
#define MATRIZ_PIN 7 // Define o pino GPIO da matriz de LEDs

void blinkLED(uint duracao){
    gpio_put(LED_PIN, 1); // Liga o LED
    sleep_ms(duracao); // Aguarda a duração
    gpio_put(LED_PIN, 0); // Desliga o LED
    sleep_ms(duracao); // Aguarda a duração
}

int main()
{
    stdio_init_all();
    gpio_init(LED_PIN); // Inicializa o pino GPIO do LED vermelho
    gpio_set_dir(LED_PIN, GPIO_OUT); // Define o pino GPIO do LED como saída
    npInit(MATRIZ_PIN); // Inicializa o pino GPIO da matriz de LEDs
    npSetLED(0, 128, 0, 0); // Define o primeiro LED da matriz de LEDs como vermelho
    npSetLED(1, 0, 255, 0); // Define o segundo LED da matriz de LEDs como verde
    npSetLED(2, 0, 0, 50); // Define o terceiro LED da matriz de LEDs como azul
    npWrite(); // Atualiza a matriz de LEDs
    while (true) {
        blinkLED(100); // LED vermelho pisca continuamente 5 vezes por segundo
    }
}
