// pwmroda4.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
// Comandos para compilacao: compila pwmroda4 -w
// ou                        g++ pwmroda4.cpp -o pwmroda4 -lwiringPi
#include <wiringPi.h>
#include <softPwm.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

void erro() {
    std::cout << ("erro");
    exit(0);
}

int main() {
    // definicoes dos pins
    const int in1 = 3;
    const int in2 = 4;
    const int in3 = 9;
    const int in4 = 10;
    wiringPiSetup();
    
    if (softPwmCreate(in1, 0, 100)) erro();
    if (softPwmCreate(in2, 0, 100)) erro();
    if (softPwmCreate(in3, 0, 100)) erro();
    if (softPwmCreate(in4, 0, 100)) erro();
    
    for (int i=0; i<2; i++) {
        // gira para a direita
        softPwmWrite(in1, 100); softPwmWrite(in2, 0); delay(2000);
        softPwmWrite(in1, 0); softPwmWrite(in2, 100); delay(2000);
        softPwmWrite(in1, 60); softPwmWrite(in2, 0); delay(2000);
        softPwmWrite(in1, 0); softPwmWrite(in2, 60); delay(2000);
        softPwmWrite(in1, 0); softPwmWrite(in2, 0); delay(2000);
        
        // gira para a esquerda
        softPwmWrite(in3, 100); softPwmWrite(in4, 0); delay(2000);
        softPwmWrite(in3, 0); softPwmWrite(in4, 100); delay(2000);
        softPwmWrite(in3, 60); softPwmWrite(in4, 0); delay(2000);
        softPwmWrite(in3, 0); softPwmWrite(in4, 60); delay(2000);
        softPwmWrite(in3, 0); softPwmWrite(in4, 0); delay(2000);
    }
}
