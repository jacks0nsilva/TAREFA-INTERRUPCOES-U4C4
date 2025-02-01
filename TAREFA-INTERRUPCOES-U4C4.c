#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "pio_config.h"
#include "hardware/timer.h"

#include "gpio_config.h" // Inclui o arquivo de configuração dos pinos GPIO


uint32_t last_time = 0;
int contador = 0;

void blinkLED(uint duracao){
    gpio_put(LED_PIN, 1); // Liga o LED
    sleep_ms(duracao); // Aguarda a duração
    gpio_put(LED_PIN, 0); // Desliga o LED
    sleep_ms(duracao); // Aguarda a duração
}

void numeroZero(){
    npClear();
    int ledsIndex[12] = {1,2,3,6,8,11,13,16,18,21,22,23};
    for(int i = 0; i < 12; i++){
        npSetLED(ledsIndex[i], 170, 60, 170);
    }
    npWrite();
}

void numeroUm(){
    npClear();
    int ledsIndex[8] = {1,2,3,7,12,16,17,22};
    for(int i = 0; i < 8; i++){
        npSetLED(ledsIndex[i], 170, 60, 170);
    }
    npWrite();
}



static void gpio_irq_handler(uint gpio, uint32_t events); // Protótipo da função de tratamento da interrupção

int main()
{
    stdio_init_all();
    initGPIO(LED_PIN, true); // Inicializa o pino GPIO do LED vermelho como saída
    npInit(MATRIZ_PIN); // Inicializa o pino GPIO da matriz de LEDs

    initGPIO(BUTTON_A_PIN, false); // Inicializa o pino GPIO do botão A como entrada
    gpio_pull_up(BUTTON_A_PIN); // Habilita o resistor de pull-up interno

    initGPIO(BUTTON_B_PIN, false); // Inicializa o pino GPIO do botão B como entrada
    gpio_pull_up(BUTTON_B_PIN); // Habilita o resistor de pull-up interno



    npWrite();
    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Habilita a interrupção no botão A
    gpio_set_irq_enabled_with_callback(BUTTON_B_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Habilita a interrupção no botão B
    while (true) {
        blinkLED(100); // LED vermelho pisca continuamente 5 vezes por segundo

        switch (contador)
        {
        case 0:
            printf("Imprimindo número 0\n");
            // Imprime o número 0 na matriz de LEDs
            numeroZero();
            break;
        case  1:
            printf("Imprimindo número 1\n");
            // Imprime o número 1 na matriz de LEDs
            numeroUm();
            break;
        case  2:
            printf("Imprimindo número 2\n");
            // Imprime o número 2 na matriz de LEDs
            npWrite();
            break;
        case 3: 
            printf("Imprimindo número 3\n");
            // Imprime o número 3 na matriz de LEDs
            npWrite();
            break;
        case 4:
            printf("Imprimindo número 4\n");
            // Imprime o número 4 na matriz de LEDs
            npWrite();
            break;
        case 5:
            printf("Imprimindo número 5\n");
            // Imprime o número 5 na matriz de LEDs
            npWrite();
            break;
        case 6:
            printf("Imprimindo número 6\n");
            // Imprime o número 6 na matriz de LEDs
            npWrite();
            break;
        case 7:
            printf("Imprimindo número 7\n");
            // Imprime o número 7 na matriz de LEDs
            npWrite();
            break;
        case 8:
            printf("Imprimindo número 8\n");
            // Imprime o número 8 na matriz de LEDs
            npWrite();
            break;
        case 9:
            printf("Imprimindo número 9\n");
            // Imprime o número 9 na matriz de LEDs
            npWrite();
            break;
        default:
            break;
        }
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
            // Incrementa o contador
            if(contador > 9){
                contador = 0; 
            } else{
                contador++;
            }
        } else if(gpio ==  BUTTON_B_PIN) { // Verifica se a interrupção foi no botão B
            // Decrementa o contador
            if(contador < 0){
                contador = 9; 
            } else{
                contador--;
            }
        }
    }
}
