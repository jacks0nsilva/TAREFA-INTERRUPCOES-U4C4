#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "pio_config.h"


#define LED_PIN 13 // Define o pino GPIO do LED vermelho

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
    while (true) {
        blinkLED(100); // LED vermelho pisca continuamente 5 vezes por segundo
    }
}
