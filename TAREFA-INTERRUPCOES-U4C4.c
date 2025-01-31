#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "pio_config.h"
#include "hardware/timer.h"

#include "gpio_config.h" // Inclui o arquivo de configuração dos pinos GPIO
int contador = 1;
int contador2 = 1;

void blinkLED(uint duracao){
    gpio_put(LED_PIN, 1); // Liga o LED
    sleep_ms(duracao); // Aguarda a duração
    gpio_put(LED_PIN, 0); // Desliga o LED
    sleep_ms(duracao); // Aguarda a duração
}

static void gpio_irq_handler(uint gpio, uint32_t events);

int main()
{
    stdio_init_all();
    initGPIO(LED_PIN, true); // Inicializa o pino GPIO do LED vermelho como saída
    npInit(MATRIZ_PIN); // Inicializa o pino GPIO da matriz de LEDs

    initGPIO(BUTTON_A_PIN, false); // Inicializa o pino GPIO do botão A como entrada
    gpio_pull_up(BUTTON_A_PIN); // Habilita o resistor de pull-up interno

    initGPIO(BUTTON_B_PIN, false); // Inicializa o pino GPIO do botão B como entrada
    gpio_pull_up(BUTTON_B_PIN); // Habilita o resistor de pull-up interno

    npSetLED(0, 255, 0, 0); // Define a cor do primeiro LED da matriz como vermelho
    npWrite();
    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Habilita a interrupção no botão A
    gpio_set_irq_enabled_with_callback(BUTTON_B_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Habilita a interrupção no botão B
    while (true) {
        blinkLED(100); // LED vermelho pisca continuamente 5 vezes por segundo
    }
}

void gpio_irq_handler(uint gpio, uint32_t events){
    if(gpio == BUTTON_A_PIN){
    printf("Botão A pressionado %d vezes!\n", contador);
    contador++;
    } else {
        printf("Botão B pressionado %d vezes!\n", contador2);
        contador2++;
    }
}
