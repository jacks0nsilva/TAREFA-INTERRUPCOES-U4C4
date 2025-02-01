#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "pio_config.h"
#include "hardware/timer.h"

#include "gpio_config.h" // Inclui o arquivo de configuração dos pinos GPIO
#include "matriz_leds.h"

static volatile uint32_t last_time = 0;
static volatile int contador = 0;


void blinkLED(uint duracao){
    gpio_put(LED_PIN, 1); // Liga o LED
    sleep_ms(duracao); // Aguarda a duração
    gpio_put(LED_PIN, 0); // Desliga o LED
    sleep_ms(duracao); // Aguarda a duração
}

static void gpio_irq_handler(uint gpio, uint32_t events); // Protótipo da função de tratamento da interrupção

int main()
{
    stdio_init_all();
    initGPIO(LED_PIN, true); // Inicializa o pino GPIO do LED vermelho como saída

    np_init(MATRIZ_PIN); // Inicializa o pino GPIO da matriz de LEDs

    initGPIO(BUTTON_A_PIN, false); // Inicializa o pino GPIO do botão A como entrada
    gpio_pull_up(BUTTON_A_PIN); // Habilita o resistor de pull-up interno

    initGPIO(BUTTON_B_PIN, false); // Inicializa o pino GPIO do botão B como entrada
    gpio_pull_up(BUTTON_B_PIN); // Habilita o resistor de pull-up interno

    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Habilita a interrupção no botão A
    gpio_set_irq_enabled_with_callback(BUTTON_B_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Habilita a interrupção no botão B
    
    np_set_leds(matriz[0],0,0,100); // Limpa a matriz de LEDs
    while (true) {
        blinkLED(100); // LED vermelho pisca continuamente 5 vezes por segundo
    }
}

// Função de tratamento da interrupção
void gpio_irq_handler(uint gpio, uint32_t events){
    // Obtem o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    // Verifica se o tempo entre as interrupções é maior que 200ms

    if(current_time - last_time > 200000){ 
        last_time = current_time;
        if(gpio == BUTTON_A_PIN){ // Verifica se a interrupção foi no botão A
                contador++; // Incrementa o contador
        } else if(gpio ==  BUTTON_B_PIN) { // Verifica se a interrupção foi no botão B
                contador--; // Decrementa o contador
        }

    // Verifica se o contador está fora do intervalo de 0 a 9    
    if(contador > 9){
        contador = 0;
    } else if(contador < 0){
        contador = 9;
    }

    np_set_leds(matriz[contador],0,0,100); // Define a cor do LED RGB para amarelo
    }
}
