//raspcam_cek.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
// Comandos para compilacao: compila raspcam_cek.cpp -c
// ou                        g++ raspcam_cek.cpp -o raspcam_cek -fmax-errors=2 `pkg-config opencv --libs --cflags` -lcekeikon -L/home/orangepi/cekeikon5/cekeikon/bin -I/home/orangepi/cekeikon5/cekeikon/src
#include <cekeikon.h>
int main() {
    VideoCapture w(1);
    
    if (!w.isOpened()) erro("Erro: Abertura de webcam 0.");
    
    w.set(CV_CAP_PROP_FRAME_WIDTH,640);
    w.set(CV_CAP_PROP_FRAME_HEIGHT,480);
    
    Mat_<COR> a;
    namedWindow("janela");

    // Objeto que gera arquivo de vídeo
    VideoWriter vo("saida.avi", CV_FOURCC('X', 'V', 'I', 'D'),
                   30, Size(640,480));
    
    int ch=-1;
    TimePoint t1=timePoint();
    int i=0;
    while (ch<0) {
        w >> a; // get a new frame from camera
        imshow("janela",a);
        ch=(signed char)(waitKey(30)); // E necessario (signed char)
        vo << a;
        i++;
    }
    TimePoint t2=timePoint();
    double t=timeSpan(t1,t2);
    printf("Quadros=%d tempo=%8.2fs fps=%8.2f\n",i,t,i/t);
}
