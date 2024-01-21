// desenha.cpp
#include <cekeikon.h>
int main() {
    Mat_<COR> a(100,100,COR(255,255,255));
    putText(a, "XY", Point(10,50), 0, 0.5, Scalar(0,0,0)); // OpenCV
    putTxt(a, 50,50,"XY"); // Cekeikon
    putTxt(a, 70,50,"ab",COR(255,0,0),2); // Cekeikon
    line(a, Point(70,10), Point(10,90), Scalar(0,0,255)); // OpenCV
    arrowedLine(a, Point(90,10), Point(30,90), Scalar(0,0,255)); // OpenCV
    flecha(a, 70,10, 10,50, COR(255,0,0)); // Cekeikon
    reta(a, 95,15, 15,75, COR(255,0,0)); // Cekeikon
    mostra(a); // Cekeikon
}