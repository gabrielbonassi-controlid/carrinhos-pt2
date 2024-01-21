// carrinho.hpp
// Classe CARRINHO
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#ifndef CARRINHO_HPP
#define CARRINHO_HPP

#include <wiringPi.h>
#include <softPwm.h>

class CARRINHO
{
    struct s_pins {
        const int in1 = 3;
        const int in2 = 4;
        const int in3 = 9;
        const int in4 = 10;
    };

    struct s_speed {
        const int fullspeed = 40;
        const int overdrive = 100;
        const int halfspeed = 20;
        const int stop = 0;
    };

    struct s_directions {
        const int forward = 8;
        const int backward = 2;
        const int stop = 5;
        const int left = 4;
        const int right = 6;
        const int bottom_left = 1;
        const int bottom_right = 3;
        const int top_left = 7;
        const int top_right = 9;
    };

    struct s_motors {
        const int left = 0;
        const int right = 1;
    };
public:
    s_motors motors;
    s_pins pins;
    s_speed speed;
    s_directions directions;
    /*
     * Constructor
     */
    
    CARRINHO();

    /*
     * Destructor
     */
    ~CARRINHO();

    void stop();
    void setMotor(s_motors& motor, s_directions& direction);
    void forward();
    void backward();
    void left();
    void right();
    void bottom_left();
    void bottom_right();
    void top_left();
    void top_right();
}