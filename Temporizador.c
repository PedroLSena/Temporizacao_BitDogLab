#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs e do botão
#define PINO_LED_AZUL     13
#define PINO_LED_VERMELHO 12
#define PINO_LED_VERDE    11
#define PINO_BOTAO        5

// Definição do intervalo do temporizador (3 segundos)
#define INTERVALO_TEMPORIZADOR_MS 3000

// Variável de controle para evitar múltiplas chamadas
bool temporizador_ativo = false;

// Função de callback do temporizador
bool callback_temporizador(struct repeating_timer *t) {
    static int estado = 0; // Controla o estado atual dos LEDs

    switch (estado) {
        case 0:
            // Primeiro estado: dois LEDs ligados
            gpio_put(PINO_LED_VERDE, 0); // Desliga o LED verde
            estado++;
            break;
        case 1:
            // Segundo estado: apenas um LED ligado
            gpio_put(PINO_LED_VERMELHO, 0); // Desliga o LED vermelho
            estado++;
            break;
        case 2:
            // Terceiro estado: todos os LEDs desligados
            gpio_put(PINO_LED_AZUL, 0); // Desliga o LED azul
            temporizador_ativo = false; // Libera o botão para nova interação
            estado = 0; // Reinicia o estado
            return false; // Para o temporizador
    }
    return true; // Continua o temporizador
}

// Função de interrupção do botão
void botao_callback(uint gpio, uint32_t events) {
    if (!temporizador_ativo) {
        // Liga todos os LEDs
        gpio_put(PINO_LED_AZUL, 1);
        gpio_put(PINO_LED_VERMELHO, 1);
        gpio_put(PINO_LED_VERDE, 1);

        // Inicia o temporizador de 3 segundos
        struct repeating_timer timer;
        add_repeating_timer_ms(INTERVALO_TEMPORIZADOR_MS, callback_temporizador, NULL, &timer);

        temporizador_ativo = true; // Bloqueia novas chamadas
    }
}

int main() {
    // Inicialização dos pinos
    stdio_init_all();

    // Configuração dos LEDs como saída
    gpio_init(PINO_LED_AZUL);
    gpio_init(PINO_LED_VERMELHO);
    gpio_init(PINO_LED_VERDE);
    gpio_set_dir(PINO_LED_AZUL, GPIO_OUT);
    gpio_set_dir(PINO_LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(PINO_LED_VERDE, GPIO_OUT);

    // Configuração do botão como entrada com pull-up
    gpio_init(PINO_BOTAO);
    gpio_set_dir(PINO_BOTAO, GPIO_IN);
    gpio_pull_up(PINO_BOTAO);

    // Configuração da interrupção do botão
    gpio_set_irq_enabled_with_callback(PINO_BOTAO, GPIO_IRQ_EDGE_FALL, true, &botao_callback);

    // Loop principal
    while (true) {
        tight_loop_contents(); // Mantém o programa rodando
    }

    return 0;
}