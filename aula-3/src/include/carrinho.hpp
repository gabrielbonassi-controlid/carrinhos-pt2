// carrinho.hpp
// Classe CARRINHO
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#ifndef CARRINHO_HPP_
#define CARRINHO_HPP_

#include <wiringPi.h>
#include <softPwm.h>
#include <cekeikon.h>

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
        const int stopspeed = 0;
    };

    enum directions {
        forward = 8,
        backward = 2,
        brake = 5,
        left = 4,
        right = 6,
        bottom_left = 1,
        bottom_right = 3,
        top_left = 7,
        top_right = 9,

    };

    enum motors {
        left_motor = 1,
        right_motor = 2
    };
public:
    s_pins pins;
    s_speed speed;
    /*
     * Constructor
     */
    
    CARRINHO();

    /*
     * Destructor
     */
    ~CARRINHO();

    void stop();
    void setMotor(int motor, int direction);
    void move_forward();
    void move_backward();
    void move_left();
    void move_right();
    void move_bottom_left();
    void move_bottom_right();
    void move_top_left();
    void move_top_right();
};

#endif // CARRINHO_HPP_