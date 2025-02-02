Temporizador de Um Disparo (One Shot) com Raspberry Pi Pico W
Este projeto implementa um sistema de temporização para acionamento de LEDs utilizando um Raspberry Pi Pico W. O sistema é controlado por um botão (pushbutton) e utiliza a função add_alarm_in_ms() da Pico SDK para criar um temporizador de 3 segundos. O código foi desenvolvido em C e pode ser simulado no Wokwi ou implementado no BitDogLab.

Funcionalidades
Acionamento dos LEDs:

Ao pressionar o botão, todos os LEDs (azul, vermelho e verde) são ligados.

Após 3 segundos, o LED verde é desligado.

Após mais 3 segundos, o LED vermelho é desligado.

Após mais 3 segundos, o LED azul é desligado, e o botão pode ser pressionado novamente.

Prevenção de Múltiplas Chamadas:

O botão só pode iniciar uma nova sequência quando o temporizador estiver inativo (todos os LEDs desligados).

Simulação e Implementação:

O código pode ser simulado no Wokwi ou implementado no BitDogLab utilizando o LED RGB e o Botão A.

Estrutura do Código
O código está organizado da seguinte forma:

Definição dos pinos:

LEDs: GPIOs 11 (verde), 12 (vermelho) e 13 (azul).

Botão: GPIO 5.

Função callback_temporizador:

Controla a mudança de estado dos LEDs a cada 3 segundos.

Função botao_callback:

É chamada quando o botão é pressionado.

Liga todos os LEDs e inicia o temporizador.

Interrupção do botão:

Configurada para detectar a borda de descida (GPIO_IRQ_EDGE_FALL) do botão.

Loop principal:

Mantém o programa em execução.

Requisitos
Hardware
Raspberry Pi Pico W.

3 LEDs (azul, vermelho e verde).

3 resistores de 330 Ω.

1 botão (pushbutton).

Jumpers e protoboard (opcional).

Software
Ambiente de desenvolvimento para Raspberry Pi Pico (por exemplo, VS Code com a extensão Pico SDK).

Compilador GCC para ARM.

Ferramenta picotool para upload do código.

Instruções de Uso
Simulação no Wokwi
Acesse o Wokwi.

Crie um novo projeto com o Raspberry Pi Pico W.

Conecte os componentes conforme o esquema:

LEDs nos GPIOs 11, 12 e 13.

Botão no GPIO 5.

Resistores de 330 Ω em série com os LEDs.

Copie e cole o código no editor do Wokwi.

Execute a simulação e pressione o botão para testar.

Implementação no BitDogLab
Conecte o LED RGB e o Botão A do BitDogLab:

LED RGB: GPIOs 11 (azul), 12 (vermelho) e 13 (verde).

Botão A: GPIO 5.

Compile o código usando o Pico SDK.

Carregue o código no Raspberry Pi Pico W utilizando picotool.

Pressione o botão para iniciar a sequência dos LEDs.