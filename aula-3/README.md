# Tarefas da Aula 3:

### Lição 1:
>Escreva camclient1.cpp e camserver1.cpp. Camserver1.cpp deve capturar os quadros coloridos 480×640 da câmera Raspberry e enviar (sem compressão) para camclient1.cpp. Camclient1.cpp deve receber os quadros e mostrá-los na tela. Apertando ESC no camclient1, deve terminar os dois programas.
><code>raspberrypi$ camserver1
>computador$ camclient1 192.168.0.110</code>

Sugestão do professor: criar mais dois métodos nas classes SERVER e CLIENT para enviar/receber imagens coloridas:

><code>void sendImg(const Mat_<COR>& img);
>void receiveImg(Mat_<COR>& img);</code>

Mais dicas na página 32 do pdf <code>rede.pdf</code>
### Lição 2:
>Modifique os programas camclient1.cpp e camserver1.cpp para criar camclient2.cpp e camserver2.cpp. A diferença é que agora os quadros devem ser enviados/recebidos com compressão JPEG. Camserver2.cpp deve capturar os quadros coloridos 480×640 da câmera Raspberry e enviar (com compressão JPEG) para camclient2.cpp. Camclient2.cpp deve receber os quadros, descompactá-los e mostrá-los na tela. Apertando ESC no camclient2, deve parar os dois programas. Mostre que seu camserver2/camclient2 funcionam.
><code>raspberrypi$ camserver2
>computador$ camclient2 192.168.0.110</code>

### Lição 3 (Também é a fase 1):
> Faça um programa servidor1.cpp para rodar na Raspberry e outro programa cliente1.cpp para rodar no computador. Estando Raspberry e computador ligados no mesmo roteador, a forma de chamar os dois programas deve ser:
> <code> raspberrypi$ servidor1
> computador$ cliente1 192.168.0.110 [videosaida.avi] [t/c]</code>
> Mostre que seu servidor1/cliente1 está funcionando. Mostre também que a gravação de vídeo funciona.

Tem uma ajuda pra essa lição, que tá na página 37 do <code>rede.pdf</code>, com o programa highgui.cpp

### Lição 4 (Também é a fase 2):
> Mostre que servidor2/cliente2 está funcionando.