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
    const int in1 = 3; //esquerda frente

    const int in2 = 4; //esquerda trás

    const int in3 = 9; //direita trás

    const int in4 = 10; //direita frente

    wiringPiSetup();

    
    if (softPwmCreate(in1, 0, 100)) erro();

    if (softPwmCreate(in2, 0, 100)) erro();

    if (softPwmCreate(in3, 0, 100)) erro();

    if (softPwmCreate(in4, 0, 100)) erro();

    
    for (int i=0;
     i<2;
     i++) {
        //
        softPwmWrite(in1, 100);
        std::cout << "in1: 100" << std::endl;
        softPwmWrite(in2, 0);
        std::cout << "in2: 0" << std::endl;
        delay(2000);

        softPwmWrite(in1, 0);
        std::cout << "in1: 0" << std::endl;
        softPwmWrite(in2, 100);
        std::cout << "in2: 100" << std::endl;
        delay(2000);

        softPwmWrite(in1, 60);
        std::cout << "in1: 60" << std::endl;
        softPwmWrite(in2, 0);
        std::cout << "in2: 0" << std::endl;
        delay(2000);

        softPwmWrite(in1, 0);
        std::cout << "in1: 0" << std::endl;
        softPwmWrite(in2, 60);
        std::cout << "in2: 60" << std::endl;
        delay(2000);

        softPwmWrite(in1, 0);
        std::cout << "in1: 0" << std::endl;
        softPwmWrite(in2, 0);
        std::cout << "in2: 0" << std::endl;
        delay(2000);

        
        // gira para a esquerda
        softPwmWrite(in3, 100);
        std::cout << "in3: 100" << std::endl;
        softPwmWrite(in4, 0);
        std::cout << "in4: 0" << std::endl;
        delay(2000);

        softPwmWrite(in3, 0);
        std::cout << "in3: 0" << std::endl;
        softPwmWrite(in4, 100);
        std::cout << "in4: 100" << std::endl;
        delay(2000);

        softPwmWrite(in3, 60);
        std::cout << "in3: 60" << std::endl;
        softPwmWrite(in4, 0);
        std::cout << "in4: 0" << std::endl;
        delay(2000);

        softPwmWrite(in3, 0);
        std::cout << "in3: 0" << std::endl;
        softPwmWrite(in4, 60);
        std::cout << "in4: 60" << std::endl;
        delay(2000);

        softPwmWrite(in3, 0);
        std::cout << "in3: 0" << std::endl;
        softPwmWrite(in4, 0);
        std::cout << "in4: 0" << std::endl;
        delay(2000);

    }
}
