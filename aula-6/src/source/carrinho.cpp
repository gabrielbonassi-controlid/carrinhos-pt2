// carrinho.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "carrinho.hpp"
#include <chrono>

#define compensa 11
#define TIME_90 1.0
#define TIME_180 1.3

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
    std::cout << "Desligando carrinho..." << std::endl;
    softPwmWrite(motor::esq_frente, speed::stopspeed);
    softPwmWrite(motor::esq_tras, speed::stopspeed);
    softPwmWrite(motor::dir_frente, speed::stopspeed);
    softPwmWrite(motor::dir_tras, speed::stopspeed);
}

void CARRINHO::stop()
{
    softPwmWrite(motor::esq_frente, speed::overdrive);
    softPwmWrite(motor::esq_tras, speed::overdrive);
    softPwmWrite(motor::dir_frente, speed::overdrive);
    softPwmWrite(motor::dir_tras, speed::overdrive);
}



void CARRINHO::move_forward() {
    softPwmWrite(motor::esq_frente, speed::overdrive - compensa);
    softPwmWrite(motor::esq_tras, speed::stopspeed);
    softPwmWrite(motor::dir_frente, speed::overdrive);
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
    softPwmWrite(motor::esq_tras, speed::fullspeed - compensa);
    softPwmWrite(motor::dir_frente, speed::stopspeed);
    softPwmWrite(motor::dir_tras, speed::fullspeed);
}

void CARRINHO::move_right() {
    softPwmWrite(motor::esq_frente, speed::fullspeed - compensa);
    softPwmWrite(motor::esq_tras, speed::stopspeed);
    softPwmWrite(motor::dir_frente, speed::stopspeed);
    softPwmWrite(motor::dir_tras, speed::fullspeed);
}

void CARRINHO::move_left() {
    softPwmWrite(motor::esq_frente, speed::stopspeed);
    softPwmWrite(motor::esq_tras, speed::fullspeed - compensa);
    softPwmWrite(motor::dir_frente, speed::fullspeed);
    softPwmWrite(motor::dir_tras, speed::stopspeed);
}

void CARRINHO::move_bottom_right() {
    softPwmWrite(motor::esq_frente, speed::stopspeed);
    softPwmWrite(motor::esq_tras, speed::fullspeed - compensa);
    softPwmWrite(motor::dir_frente, speed::stopspeed);
    softPwmWrite(motor::dir_tras, speed::halfspeed);
}

void CARRINHO::move_bottom_left() {
    softPwmWrite(motor::esq_frente, speed::stopspeed);
    softPwmWrite(motor::esq_tras, speed::halfspeed - compensa);
    softPwmWrite(motor::dir_frente, speed::stopspeed);
    softPwmWrite(motor::dir_tras, speed::fullspeed);
}

void CARRINHO::move_top_right() {
    softPwmWrite(motor::esq_frente, speed::fullspeed - compensa);
    softPwmWrite(motor::esq_tras, speed::stopspeed);
    softPwmWrite(motor::dir_frente, speed::halfspeed);
    softPwmWrite(motor::dir_tras, speed::stopspeed);
}

void CARRINHO::move_top_left() {
    softPwmWrite(motor::esq_frente, speed::halfspeed - compensa);
    softPwmWrite(motor::esq_tras, speed::stopspeed);
    softPwmWrite(motor::dir_frente, speed::fullspeed);
    softPwmWrite(motor::dir_tras, speed::stopspeed);
}

void CARRINHO::turn90left(const TimePoint &t1, bool &finished) {
    TimePoint t2 = timePoint();
    double t = timeSpan(t1, t2);
    // auto t2 = std::chrono::high_resolution_clock::now();
    // // double t = timeSpan(t1, t2);
    // auto t = std::chrono::duration_cast<std::chrono::seconds>(t2-t1);
    std::cout << "Tempo percorrido: " << t << std::endl;
    if (t < TIME_90) {
        this->move_left();
    } else {
        finished = true;
        this->stop();
    }
}

void CARRINHO::turn90right(const TimePoint &t1, bool &finished) {
    TimePoint t2 = timePoint();
    double t = timeSpan(t1, t2);
    // auto t2 = std::chrono::high_resolution_clock::now();
    // // double t = timeSpan(t1, t2);
    // auto t = std::chrono::duration_cast<std::chrono::seconds>(t2-t1);
    std::cout << "Tempo percorrido: " << t << std::endl;
    if (t < TIME_90) {
        this->move_right();
    } else {
        finished = true;
        this->stop();
    }
}

void CARRINHO::turn180left(const TimePoint &t1, bool &finished) {
    TimePoint t2 = timePoint();
    double t = timeSpan(t1, t2);
    // auto t2 = std::chrono::high_resolution_clock::now();
    // // double t = timeSpan(t1, t2);
    // auto t = std::chrono::duration_cast<std::chrono::seconds>(t2-t1);
    // std::cout << "Tempo percorrido: " << t.count() << std::endl;
    std::cout << "Tempo percorrido: " << t << std::endl;
    if (t < TIME_180) {
        this->move_left();
    } else {
        finished = true;
        this->stop();
    }
}

void CARRINHO::turn180right(const TimePoint &t1, bool &finished) {
    TimePoint t2 = timePoint();
    double t = timeSpan(t1, t2);
    // auto t2 = std::chrono::high_resolution_clock::now();
    // // double t = timeSpan(t1, t2);
    // auto t = std::chrono::duration_cast<std::chrono::seconds>(t2-t1);
    std::cout << "Tempo percorrido: " << t << std::endl;
    if (t < TIME_180) {
        this->move_right();
    } else {
        finished = true;
        this->stop();
    }
}

void CARRINHO::move_under(const TimePoint &t1, bool &finished) {
    // auto t2 = std::chrono::high_resolution_clock::now();
    TimePoint t2 = timePoint();
    double t = timeSpan(t1, t2);
    // auto t = std::chrono::duration_cast<std::chrono::seconds>(t2-t1);
    std::cout << "Tempo percorrido: " << t << std::endl;
    if (t < 1.8) {
        this->move_forward();
    } else {
        finished = true;
        this->stop();
    }
}