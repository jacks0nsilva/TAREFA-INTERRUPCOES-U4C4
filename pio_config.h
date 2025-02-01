#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h" 
#include "ws2812.pio.h"


#define LEDS_COUNT 25 // Define a quantidade de LEDs da matriz


struct pixel_t {
    uint8_t G, R, B; // Três valores de 8 bits para cada cor
};

typedef struct pixel_t pixel_t; // Define o tipo de dado pixel_t
typedef pixel_t npLED_p; // Mudança de nome para facilidar a leitura do código

npLED_p leds[LEDS_COUNT]; // Buffer de pixels que será enviado para o microcontrolador

// Função que converte as cors em formato RGB para o protocolo da matriz de LEDs
// O protocolo é 24 bits, sendo 8 bits para cada cor (G, R, B)
uint32_t matriz_rgb(uint8_t r, uint8_t g, uint8_t b){
    unsigned char R,G,B;
    R = (unsigned char)r;
    G = (unsigned char)g;
    B = (unsigned char)b;
    return (G << 24) | (R << 16) | (B << 8);
}

// Variáveis para o controle da máquina PIO
PIO np_pio;
uint np_sm;

// Inicializa a máquina PIO
void npInit(uint pin){
    // Cria uma instância da máquina PIO
    uint offset = pio_add_program(pio0, &ws2812_program);
    np_pio = pio0;

    // Aloca uma máquina PIO
    np_sm = pio_claim_unused_sm(np_pio, false);
    if(np_sm < 0){
        np_pio = pio1;
        np_sm = pio_claim_unused_sm(np_pio, true); // Se não houver máquinas disponíveis, panic
    }

    // Inicializa a máquina PIO com o programa ws2812_program
    ws2812_program_init(np_pio, np_sm, offset,pin, 800000, false);

    // Limpa o buffer de LEDs
    for(uint i = 0; i < LEDS_COUNT; i++){
        leds[i].R = 0;
        leds[i].G = 0;
        leds[i].B = 0;
    }
}

// Atribui uma cor a um LED específico
void npSetLED(const uint index, const uint8_t R, const uint8_t G, const uint8_t B){
    leds[index].R = R;
    leds[index].G = G;
    leds[index].B = B;
}

// Limpa o buffer de LEDs
void npClear(){
    for(uint i = 0; i < LEDS_COUNT; i++){
        leds[i].R = 0;
        leds[i].G = 0;
        leds[i].B = 0;
    }
}

// Escreve o buffer de LEDs no controlador
void npWrite(){
    // Escreve cada dado de 8 bits no buffer da máquina PIO
    for(uint i = 0; i < LEDS_COUNT; i++){
        uint32_t valor_led = matriz_rgb(leds[i].R, leds[i].G, leds[i].B);
        pio_sm_put_blocking(np_pio, np_sm, valor_led);
    }
    sleep_us(100); // Espera 100us para garantir que todos os dados foram enviados
}
