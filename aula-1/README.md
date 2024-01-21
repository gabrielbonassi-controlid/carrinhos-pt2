# Aula 1:
### Lição 1:
>  Mostre "ssh -X" funcionando.

Simplesmente conectar ao raspberry pi usando <code>ssh -X \<pi@raspberry-ip></code>

### Lição 2:
> Mostre sshfs funcionando. Pode mostrar o acesso ao diretório do Raspberry via terminal e/ou via gerenciador de arquivos

Via terminal né

### Lição 3:
> Modifique o programa raspcam_cek ou raspcam_ocv para criar raspvid.cpp que, além de mostrar a captura de 
câmera na tela, grava os quadros num vídeo.
>
>Exemplo: <code>$ raspvid saida.avi</code>
>
>Deve gerar vídeo saida.avi com os quadros capturados pela câmera. Os comandos para gerar vídeo de saída são basicamente:
>``` c++
>...
>VideoWriter vo("nomevideo.avi",CV_FOURCC('X','V','I','D'), 30,Size(640,480));
>...
>while (true) {
>    w >> a;
>...
>    vo << a;
>...
>}
>```

**Obs: existe um código na apostila <code>raspicam_wiringpi.pdf</code> que imprime quantos quadros por segundo o programa consegue mostrar na tela do pc**

### Lição 4:
> Monte o carrinho “de forma caprichada”, com todos os componentes firmemente fixados no chassis e sem “fios soltos”. Ligue o Raspberry e os motores no Powerbank. Faça conexão VNC ou SSH entre o Raspberry e o computador. A partir do computador, rode o programa pwmroda4 no Raspberry. O carrinho deve girar para direita com velocidade total e depois com meia velocidade; e em seguida deve girar para esquerda com velocidade total e depois com meia velocidade. Se o carrinho se movimentar excessivamente, acerte os parâmetros do programa. A qualidade de montagem do carrinho será levada em consideração ao atribuir a nota. Mostre ao professor (ou grave no vídeo) o carrinho se movimentando.