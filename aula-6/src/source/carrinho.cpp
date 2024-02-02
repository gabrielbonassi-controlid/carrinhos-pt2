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

void CARRINHO::move_forward(int dist, bool direction) {
    if (direction) { //direita tem que ser mais rapida que esquerda
        softPwmWrite(motor::esq_frente, (speed::halfspeed - dist) );
        softPwmWrite(motor::esq_tras, speed::stopspeed);
        softPwmWrite(motor::dir_frente, speed::halfspeed);
        softPwmWrite(motor::dir_tras, speed::stopspeed);
    } else {
        softPwmWrite(motor::esq_frente, speed::halfspeed);
        softPwmWrite(motor::esq_tras, speed::stopspeed);
        softPwmWrite(motor::dir_frente, (speed::halfspeed - dist));
        softPwmWrite(motor::dir_tras, speed::stopspeed);
    }
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

void CARRINHO::turn90left(TimePoint &t1, bool &finished) {
    // TimePoint t2 = timePoint();
    // double t = timeSpan(t1, t2);
    auto t2 = std::chrono::high_resolution_clock::now();
    // double t = timeSpan(t1, t2);
    auto t = std::chrono::duration_cast<std::chrono::seconds>(t1 - t2);
    std::cout << "Tempo percorrido: " << t << std::endl;
    if (t < 1.4) {
        this->move_left();
    } else {
        finished = true;
        this->stop();
    }
}

void CARRINHO::turn90right(TimePoint &t1, bool &finished) {
    // TimePoint t2 = timePoint();
    // double t = timeSpan(t1, t2);
    auto t2 = std::chrono::high_resolution_clock::now();
    // double t = timeSpan(t1, t2);
    auto t = std::chrono::duration_cast<std::chrono::seconds>(t1 - t2);
    std::cout << "Tempo percorrido: " << t << std::endl;
    if (t < 1.4) {
        this->move_right();
    } else {
        finished = true;
        this->stop();
    }
}

void CARRINHO::turn180left(TimePoint &t1, bool &finished) {
    // TimePoint t2 = timePoint();
    // double t = timeSpan(t1, t2);
    auto t2 = std::chrono::high_resolution_clock::now();
    // double t = timeSpan(t1, t2);
    auto t = std::chrono::duration_cast<std::chrono::seconds>(t1 - t2);
    std::cout << "Tempo percorrido: " << t << std::endl;
    if (t < 2.8) {
        this->move_left();
    } else {
        finished = true;
        this->stop();
    }
}

void CARRINHO::turn180right(TimePoint &t1, bool &finished) {
    // TimePoint t2 = timePoint();
    // double t = timeSpan(t1, t2);
    auto t2 = std::chrono::high_resolution_clock::now();
    // double t = timeSpan(t1, t2);
    auto t = std::chrono::duration_cast<std::chrono::seconds>(t1 - t2);
    std::cout << "Tempo percorrido: " << t << std::endl;
    if (t < 2.8) {
        this->move_right();
    } else {
        finished = true;
        this->stop();
    }
}

void CARRINHO::move_under(const std::chrono::high_resolution_clock::time_point &t1, bool &finished) {
    std::cout << "Passando pela placa" << std::endl;
    auto t2 = std::chrono::high_resolution_clock::now();
    // double t = timeSpan(t1, t2);
    auto t = std::chrono::duration_cast<std::chrono::seconds>(t1 - t2);
    std::cout << "Tempo percorrido: " << t << std::endl;
    if (t < 2.0) {
        this->move_forward();
    } else {
        finished = true;
        this->stop();
    }
}