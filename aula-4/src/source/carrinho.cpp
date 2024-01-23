// carrinho.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "carrinho.hpp"

CARRINHO::CARRINHO()
{   
    std::cout << "Inicializando carrinho..." << std::endl;
    wiringPiSetup();
    if (softPwmCreate(motor::esq_frente, 0, 100))
        erro("ERRO PIN3\n");
    if (softPwmCreate(motor::esq_tras, 0, 100))
        erro("ERRO PIN4\n");
    if (softPwmCreate(motor::dir_frente, 0, 100))
        erro("ERRO PIN9\n");
    if (softPwmCreate(motor::dir_tras, 0, 100))
        erro("ERRO PIN12\n");
}

CARRINHO::~CARRINHO()
{
}

void CARRINHO::stop()
{
    softPwmWrite(motor::esq_frente, speed::overdrive);
    softPwmWrite(motor::esq_tras, speed::overdrive);
    softPwmWrite(motor::dir_frente, speed::overdrive);
    softPwmWrite(motor::dir_tras, speed::overdrive);
}



void CARRINHO::move_forward() {
    softPwmWrite(motor::esq_frente, speed::fullspeed);
    softPwmWrite(motor::esq_tras, speed::stopspeed);
    softPwmWrite(motor::dir_frente, speed::fullspeed);
    softPwmWrite(motor::dir_tras, speed::stopspeed);
}

void CARRINHO::move_backward() {
    softPwmWrite(motor::esq_frente, speed::stopspeed);
    softPwmWrite(motor::esq_tras, speed::fullspeed);
    softPwmWrite(motor::dir_frente, speed::stopspeed);
    softPwmWrite(motor::dir_tras, speed::fullspeed);
}

void CARRINHO::move_right() {
    softPwmWrite(motor::esq_frente, speed::fullspeed);
    softPwmWrite(motor::esq_tras, speed::stopspeed);
    softPwmWrite(motor::dir_frente, speed::stopspeed);
    softPwmWrite(motor::dir_tras, speed::fullspeed);
}

void CARRINHO::move_left() {
    softPwmWrite(motor::esq_frente, speed::stopspeed);
    softPwmWrite(motor::esq_tras, speed::fullspeed);
    softPwmWrite(motor::dir_frente, speed::fullspeed);
    softPwmWrite(motor::dir_tras, speed::stopspeed);
}

void CARRINHO::move_bottom_right() {
    softPwmWrite(motor::esq_frente, speed::stopspeed);
    softPwmWrite(motor::esq_tras, speed::fullspeed);
    softPwmWrite(motor::dir_frente, speed::stopspeed);
    softPwmWrite(motor::dir_tras, speed::halfspeed);
}

void CARRINHO::move_bottom_left() {
    softPwmWrite(motor::esq_frente, speed::stopspeed);
    softPwmWrite(motor::esq_tras, speed::halfspeed);
    softPwmWrite(motor::dir_frente, speed::stopspeed);
    softPwmWrite(motor::dir_tras, speed::fullspeed);
}

void CARRINHO::move_top_right() {
    softPwmWrite(motor::esq_frente, speed::fullspeed);
    softPwmWrite(motor::esq_tras, speed::stopspeed);
    softPwmWrite(motor::dir_frente, speed::halfspeed);
    softPwmWrite(motor::dir_tras, speed::stopspeed);
}

void CARRINHO::move_top_left() {
    softPwmWrite(motor::esq_frente, speed::halfspeed);
    softPwmWrite(motor::esq_tras, speed::stopspeed);
    softPwmWrite(motor::dir_frente, speed::fullspeed);
    softPwmWrite(motor::dir_tras, speed::stopspeed);
}