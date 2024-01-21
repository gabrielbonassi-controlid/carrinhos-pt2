// cekraspcam2.cpp
// Exemplo de captura de imagem 480x640 do raspicam, imprimindo fps
// compila cekraspcam2 -c
#include <cekeikon.h>
int main () {
VideoCapture cam(0);
    Mat_<COR> image;
    cam.set(CV_CAP_PROP_FRAME_WIDTH,640);
    cam.set(CV_CAP_PROP_FRAME_HEIGHT,480);
    namedWindow("janela",1);
    int ch=-1;
    TimePoint t1=timePoint();
    int i=0;
    while (ch<0) {
        cam >> image;
        imshow("janela",image);
        ch=(signed char)waitKey(1);
        i++;
    }
    TimePoint t2=timePoint();
    double t=timeSpan(t1,t2);
    printf("Quadros=%d tempo=%8.2fs fps=%8.2f\n",i,t,i/t);
}