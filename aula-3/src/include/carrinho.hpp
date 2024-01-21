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

class CARRINHO
{

    enum motor {
        esq_frente = 3,
        esq_tras = 4,
        dir_frente = 10,
        dir_tras = 9
    };

    enum speed {
        fullspeed = 100,
        overdrive = 100,
        halfspeed = 60,
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
    void move_backward();
    void move_left();
    void move_right();
    void move_bottom_left();
    void move_bottom_right();
    void move_top_left();
    void move_top_right();
};

#endif // CARRINHO_HPP_