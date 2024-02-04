// carrinho.hpp
// Classe CARRINHO
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#ifndef CARRINHO_HPP_
#define CARRINHO_HPP_

#include <wiringPi.h>
#include <softPwm.h>
#include <cekeikon.h>
#include <stdio.h>
#include <thread>
#include <chrono>

class CARRINHO
{

    enum motor {
        esq_frente = 3,
        esq_tras = 4,
        dir_frente = 10,
        dir_tras = 9
    };

    enum speed {
        fullspeed = 70,
        overdrive = 100,
        halfspeed = 50,
        slowspeed = 40,
        stopspeed = 0
    };
public:
    /*
     * Constructor
     */
    
    CARRINHO();

    /*
     * Destructor
     */
    ~CARRINHO();

    void stop();
    void move_forward();
    void move_forward(int dist, bool direction); // true = esquerda, false = direita
    void move_forward_slow();
    void move_backward();
    void move_left();
    void move_right();
    void move_bottom_left();
    void move_bottom_right();
    void move_top_left();
    void move_top_right();

    void turn90left(const TimePoint &t1, bool &finished);
    void turn90right(const TimePoint &t1, bool &finished);
    void turn180left(const TimePoint &t1, bool &finished);
    void turn180right(const TimePoint &t1, bool &finished);
    void move_under(const TimePoint &t1, bool &finished);
};

#endif // CARRINHO_HPP_