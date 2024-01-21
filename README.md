# Fases 1 e 2 do projeto:
## Fase 1 - Transmissão de vídeo e comandos

**Objetivo:** Criar uma arquitetura servidor-cliente, onde o servidor é o raspberry pi e o cliente é o nosso PC.

O formato da chamada dos programas deve ser:

```
raspberrypi$ servidor1
computador$ cliente1 192.168.0.110 [videosaida.avi] [t/c]
```
Onde:
- 192.168.0.110 é o endereço IP da Raspberry.
- Videosaida.avi é o nome do vídeo onde as imagens mostradas na tela ou capturadas pela câmera serão armazenadas. Se o vídeo de saída não for especificado, o conteúdo da tela não será gravado.
- O argumento t ou c indica respectivamente gravar uma cópia da tela (com teclado virtual - default) ou somente a imagem capturada pela câmera. Usando o argumento t, quadros como a figura 15 serão gravados. Usando o argumento c, serão gravados somente a imagem capturada pela câmera

O funcionamento do programa deve ser:
1) O usuário inicia o programa servidor1 no Raspberry e espera receber conexão do computador.
2) O usuário inicia o programa cliente1 no computador. O computador envia uma mensagem (por exemplo, “0”) ao Raspberry para dizer que está pronto para receber uma imagem.
3) Raspberry (servidor1) recebe a mensagem e captura uma imagem colorida 240×320 da câmera, compacta-a e envia-a ao computador. 
4) Computador (cliente1) recebe a imagem compactada, descompacta-a, “gruda-a” ao teclado virtual horizontalmente e mostra-a na janela (e salva-a no vídeo se o vídeo de saída tiver sido especificado, modo t com teclado numérico ou c sem teclado numérico).
5) O usuário visualiza a imagem com teclado virtual numa janela do computador. Se o usuário apertou ESC no computador, cliente1 envia uma mensagem (por exemplo, “s”) para terminar o programa servidor1 no Raspberry. Neste caso, além disso, finaliza o programa cliente1 no computador. Caso contrário, cliente1 verifica se o usuário apertou algum botão virtual (1 a 9). Nesse caso, cliente1 envia o código do botão virtual apertado (“1” a “9”). Se nenhum botão virtual tiver sido apertado, envia uma mensagem (por exemplo, “0”) a servidor1.
6) Raspberry (servidor1) recebe a mensagem (“s” para terminar o programa, “0” indicando não-pressionamento do botão virtual, “1” a “9” indicando o botão virtual apertado). Se a mensagem for “s”, termina o programa. Caso contrário, insere a mensagem no canto superior esquerdo do quadro a ser enviado ao computador. A direção a seguir deve ser indicada na imagem pelo programa servidor1 no Raspberry antes de ser transmitida ao cliente1 no computador, para mostrar que recebeu corretamente o comando. Na figura 1, foi selecionada “ir para frente” correspondente à tecla “8”. Raspberry captura uma imagem colorida 240×320 da câmera, compacta-a e envia-a ao computador.
7) Repete a partir da linha (4).

## Fase 2 - Controle remoto manual do carrinho com transmissão de vídeo

**Objetivo:** Controlar manualmente o carrinho à distância, com a transmissão da captura da câmera em tempo real. O controle e a transmissão são feitos usando os programas da fase anterior, ou seja: o grande diferencial da fase 2 é o controle do carrinho.

>Para compilar um programa no Raspberry e linkar com WiringPi (além de Cekeikon e OpenCV), você deve usar a opção “-w”:
>
><code>raspberrypi$ compila servidor2 -c -w</code>

O funcionamento da fase 2 é:
1) O usuário inicia o programa servidor1 no Raspberry e espera receber conexão do computador.
2) O usuário inicia o programa cliente1 no computador. O computador envia uma mensagem (por exemplo, “0”) ao Raspberry para dizer que está pronto para receber uma imagem.
3) Raspberry (servidor1) recebe a mensagem e captura uma imagem colorida 240×320 da câmera, compacta-a e envia-a ao computador.
4) Computador (cliente1) recebe a imagem compactada, descompacta-a, “gruda-a” ao teclado virtual horizontalmente e mostra-a na janela (e salva-a no vídeo se o vídeo de saída tiver sido especificado, modo t com teclado numérico ou c sem teclado numérico).
5) O usuário visualiza a imagem com teclado virtual numa janela do computador. Se o usuário apertou ESC no computador, cliente1 envia uma mensagem (por exemplo, “s”) para terminar o programa servidor1 no Raspberry. Neste caso, além disso, finaliza o programa cliente1 no computador. Caso contrário, cliente1 verifica se o usuário apertou algum botão virtual (1 a 9). Nesse caso, cliente1 envia o código do botão virtual apertado (“1” a “9”). Se nenhum botão virtual tiver sido apertado, envia uma mensagem (por exemplo, “0”) a servidor1.
6) 6) Raspberry (servidor1) recebe a mensagem (“s” para terminar o programa, “0” indicando não-pressionamento do botão virtual, “1” a “9” indicando o botão virtual apertado). Se a mensagem for “s”, termina o programa. Caso contrário, movimenta os motores de acordo com a mensagem recebida. Raspberry captura uma imagem colorida 240×320 da câmera, compacta-a e envia-a ao computador.
7) Repete a partir da linha (4).

## Fase 3:
**Objetivo:** Fazer um programa que identifique uma placa (disponível no arquivo aula-4/quadrado.png) utilizando template matching.

## Fase 4:
**Objetivo:** Modificar o programa da fase 3 para controlar o carrinho de forma que ele siga continuamente a placa.

O carrinho deve parar nas duas situações:
1) Quando não conseguir localizar a placa no quadro do vídeo capturado.
2) Quando a câmera do Raspberry estiver muito próximo da placa, para evitar uma colisão.

## Fase 5:
**Objetivo:** Modificar o programa da fase 3 para que ele reconheça um número dentro do quadrado, usando o dataset MNIST.

## Fase 6:
**Objetivo:** Juntar tudo e implementar comandos para controlar o carrinho, baseado nos números dentro do quadrado que o carrinho irá ler. Os comandos são:
- 0 ou 1: Pare o carrinho.
- 2: Vire 180 graus à esquerda imediatamente.
- 3: Vire 180 graus à direita imediatamente.
- 4 ou 5: Passe por baixo da placa e continue em frente.
- 6 ou 7: Vire 90 graus à esquerda imediatamente.
- 8 ou 9: Vire 90 graus à direita imediatamente.

## Fase 7:
**Objetivo:** Misturar o controle manual da fase 2 com o controle automâtico da fase 6.

Para que o usuário possa controlar o carrinho inteiramente à distância, nesta fase vamos misturar o controle manual (fase 2, apostila rede) com o controle automático (fase 6 desta apostila).

O sistema deve começar no modo “manual”, mostrando uma tela igual à desenvolvida na fase 2. O usuário poderá controlar o carrinho manualmente para colocar o carrinho na posição inicial da trajetória automática. Neste momento, o usuário aperta o botão virtual “M/A” e o carrinho passa para o controle automático, seguindo as placas e obedecendo aos comandos escritos nas placas.

Quando chegar no final da trajetória automática, o controle volta para o modo manual. Além disso, a qualquer momento o usuário pode reassumir o controle manual do carrinho apertando a tecla virtual “M/A”. 

#### Observações adicionais:
- Utilizamos a resolução de 240x320 no projeto para melhorar a taxa de fps.
- Ao invés de usar um Raspberry Pi 3 Model B, como usado na disciplina, usamos um Orange Pi 3 LTS, que tem configs bem parecidas (e é bem mais barato).