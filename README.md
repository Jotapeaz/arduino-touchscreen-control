# Arduino-touchscreen-control
Este projeto utiliza uma matriz sensora feita com multiplexadores e sensores de infravermelho para controlar o ponteiro do mouse em um computador, via Arduino Leonardo. O sistema identifica a posição pressionada na matriz e move o cursor do mouse para essa coordenada na tela.

# Componetes utilizados 

* Arduino Leonardo (requerido para suporte nativo ao controle do mouse)
  
* 2x Multiplexadores (74HC4067 ou similar)
  
* Sensores analógicos (pode ser LDRs, botões, ou sensores de toque resistivo)

* Botão físico (para reset/emergência)

* 26x LEDs emissores 
* 26x LEDs recptores 

* Bibliotecas:
* Mouse.h (nativa do Arduino para Leonardo)
* MouseTo.h (controle absoluto do ponteiro)

# Funcionalidades
* Leitura de 16x10 pontos sensoriais usando multiplexadores.
* Cálculo da posição do clique com base nas leituras analógicas.
* Movimento do cursor do mouse com precisão absoluta.
* Sistema de segurança para desativar o mouse por 1 minuto com botão físico.

# Instalação
1. Monte o circuito:

* Conecte os multiplexadores nos pinos digitais e analógicos indicados no código.

* Conecte o botão de segurança ao pino 13.

* Conecte um LED ao pino A3.

2. Código:

* Faça upload do código mouse_matrix.ino para o Arduino Leonardo.

* Certifique-se de instalar a biblioteca MouseTo.h (caso não tenha, baixe e instale manualmente via ZIP ou Library Manager).

3. Teste:

* Pressione pontos da matriz sensora.

* O cursor deverá se mover conforme a posição lida.

* Pressione o botão de segurança para pausar o mouse por 60 segundos.
