# Tarefas da Aula 4:
### Lição 1 (Também é a fase 3):
> Faça um programa fase3.cpp que lê um vídeo 240×320 pixels (capturado.avi, capturado2.avi ou capturado3.avi), um modelo de placa (quadrado.png) e localiza a placa-modelo nos seus quadros, toda vez que a placa estiver entre aproximadamente 30 e 150 cm da câmera, gerando o vídeo de saída com a localização da placa (figura 4). Imprima também quantos quadros/segundo o seu programa conseguiu processar.

Existe uma dica útil para imprimir quantos quadros/segundo o programa conseguiu processar na apostila <code>raspicam_wiringpi.pdf</code>, página 6. É o programa cekraspcam2.cpp

Os arquivos necessários pra essa lição estão nessa pasta.

### Lição 2:
> Acelere o programa fase3 usando o processamento paralelo OpenMP (“compila fase3 -c -v3 -omp”). O importante é paralelizar os casamentos de modelos, pois é a parte mais “pesada” do programa. Calcule quadros/segundo do seu programa paralelo. O programa paralelo está mais rápido do que o programa sequencial?

### Lição 3 (Também é a fase 4):
> Modifique o programa da fase 3 para controlar o carrinho de forma que ele siga continuamente a placa quadrado.png. Para isso, você irá usar somente a posição x da localização da placa, desprezando a posição y.

Ajuda útil do professor:
> **Como eu fiz**: Fiz com que a diferença das velocidades das rodas esquerda e direita seja diretamente proporcional à distância entre a posição x da placa e o centro da imagem. Isto é, se a placa estiver muito à esquerda, o carrinho irá girar rapidamente para esquerda. Se a placa estiver ligeiramente fora do centro, o carrinho irá corrigir a rota suavemente. Isto faz com que o movimento do carrinho fique “suave”