Projeto de Olhos Robôs com Display OLED e Sensores Ultrassônicos

Este projeto é um robô interativo que exibe diferentes expressões faciais em um display OLED de 128x64 pixels, utilizando sensores ultrassônicos HC-SR04 para detecção de proximidade e botões para alterar emoções. O robô "emocional" pode expressar diferentes estados: neutro, feliz, triste, raiva, além de possuir um efeito de piscar.

Componentes Utilizados:

Microcontrolador Arduino Uno
Display OLED SSD1306 (128x64)
2 Sensores Ultrassônicos HC-SR04
2 Botões
Biblioteca Wire
Biblioteca Adafruit GFX
Biblioteca Adafruit SSD1306

Funcionalidades Principais
Movimentação dos Olhos

Os olhos se movem horizontalmente com base na distância detectada pelos sensores ultrassônicos da esquerda e direita
A função updateEyePosition() ajusta a posição dos olhos de acordo com as distâncias medidas

Expressões Faciais

Olhar Neutro: Padrão do robô
Olhar Bravo: Ativado pelo botão de raiva, com sombreamento nos cantos dos olhos
Olhar Triste: Ativado pelo botão de tristeza, com modificação na forma dos olhos
Olhar Feliz: Exibido periodicamente, com contorno dos olhos e parte inferior limpa
Piscar: Ocorre periodicamente, simulando um piscar natural

Configuração dos Pinos

Sensores Ultrassônicos:

Esquerdo: Trigger no pino 7, Echo no pino 6
Direito: Trigger no pino 5, Echo no pino 4

Botões:

Botão de Tristeza no pino 3
Botão de Raiva no pino 2

Display OLED no endereço I2C 0x3C

Lógica de Funcionamento

No setup(), inicializa comunicação I2C, display, pinos de entrada/saída e comunicação serial
No loop(), principais ações:

Leitura dos sensores ultrassônicos
Atualização da posição dos olhos
Verificação do estado dos botões
Alteração das expressões faciais

Ciclos temporais controlam piscar e expressões alternadas

Como Usar

Monte o circuito conforme a descrição de pinos
Carregue o código no Arduino
Interaja com os botões ou aproxime objetos dos sensores ultrassônicos

Possíveis Melhorias

Adicionar mais estados emocionais
Implementar sensor de som ou movimento
Criar padrões de movimento mais complexos
Adicionar feedback sonoro

Bibliotecas Necessárias

Wire
Adafruit_GFX
Adafruit_SSD1306
