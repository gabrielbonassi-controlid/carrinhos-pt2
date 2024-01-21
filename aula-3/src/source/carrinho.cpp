// carrinho.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "carrinho.hpp"

CARRINHO::CARRINHO()
{
    wiringPiSetup();
    if (softPwmCreate(this->pins.in1, 0, 100))
        erro("ERRO PIN3\n");
    if (softPwmCreate(this->pins.in2, 0, 100))
        erro("ERRO PIN4\n");
    if (softPwmCreate(this->pins.in3, 0, 100))
        erro("ERRO PIN9\n");
    if (softPwmCreate(this->pins.in4, 0, 100))
        erro("ERRO PIN12\n");
}

CARRINHO::~CARRINHO()
{
    stop();
}

void CARRINHO::stop()
{
    softPwmWrite(this->pins.in1, this->speed.stopspeed);
    softPwmWrite(this->pins.in2, this->speed.stopspeed);
    softPwmWrite(this->pins.in3, this->speed.stopspeed);
    softPwmWrite(this->pins.in4, this->speed.stopspeed);
    digitalWrite(this->pins.in1, LOW);
    digitalWrite(this->pins.in2, LOW);
    digitalWrite(this->pins.in3, LOW);
    digitalWrite(this->pins.in4, LOW);
}

void CARRINHO::setMotor(int motor, int direction) {
    switch (motor) {
        case motors::left_motor:
            switch (direction) {
                case directions::forward:
                    softPwmWrite(this->pins.in1, this->speed.overdrive);
                    softPwmWrite(this->pins.in2, this->speed.stopspeed);
                    break;
                case directions::backward:
                    softPwmWrite(this->pins.in1, this->speed.stopspeed);
                    softPwmWrite(this->pins.in2, this->speed.fullspeed);
                    break;
                case directions::brake:
                    softPwmWrite(this->pins.in1, this->speed.overdrive);
                    softPwmWrite(this->pins.in2, this->speed.overdrive);
                    break;
                case directions::left:
                    softPwmWrite(this->pins.in1, this->speed.fullspeed);
                    softPwmWrite(this->pins.in2, this->speed.stopspeed);
                    break;
                case directions::right:
                    softPwmWrite(this->pins.in1, this->speed.stopspeed);
                    softPwmWrite(this->pins.in2, this->speed.fullspeed);
                    break;
                case directions::bottom_left:
                    softPwmWrite(this->pins.in1, this->speed.stopspeed);
                    softPwmWrite(this->pins.in2, this->speed.fullspeed);
                    break;
                case directions::bottom_right:
                    softPwmWrite(this->pins.in1, this->speed.stopspeed);
                    softPwmWrite(this->pins.in2, this->speed.halfspeed);
                    break;
                case directions::top_left:
                    softPwmWrite(this->pins.in1, this->speed.fullspeed);
                    softPwmWrite(this->pins.in2, this->speed.stopspeed);
                    break;
                case directions::top_right:
                    softPwmWrite(this->pins.in1, this->speed.halfspeed);
                    softPwmWrite(this->pins.in2, this->speed.stopspeed);
                    break;
                default:
                    stop();
                    break;
            }
        case motors::right_motor:
            switch (direction) {
                case directions::forward:
                    softPwmWrite(this->pins.in3, this->speed.overdrive);
                    softPwmWrite(this->pins.in4, this->speed.stopspeed);
                    break;
                case directions::backward:
                    softPwmWrite(this->pins.in3, this->speed.stopspeed);
                    softPwmWrite(this->pins.in4, this->speed.fullspeed);
                    break;
                case directions::brake:
                    softPwmWrite(this->pins.in3, this->speed.overdrive);
                    softPwmWrite(this->pins.in4, this->speed.overdrive);
                    break;
                case directions::left:
                    softPwmWrite(this->pins.in3, this->speed.stopspeed);
                    softPwmWrite(this->pins.in4, this->speed.fullspeed);
                    break;
                case directions::right:
                    softPwmWrite(this->pins.in3, this->speed.fullspeed);
                    softPwmWrite(this->pins.in4, this->speed.stopspeed);
                    break;
                case directions::bottom_left:
                    softPwmWrite(this->pins.in3, this->speed.stopspeed);
                    softPwmWrite(this->pins.in4, this->speed.halfspeed);
                    break;
                case directions::bottom_right:
                    softPwmWrite(this->pins.in3, this->speed.stopspeed);
                    softPwmWrite(this->pins.in4, this->speed.fullspeed);
                    break;
                case directions::top_left:
                    softPwmWrite(this->pins.in3, this->speed.halfspeed);
                    softPwmWrite(this->pins.in4, this->speed.stopspeed);
                    break;
                case directions::top_right:
                    softPwmWrite(this->pins.in3, this->speed.fullspeed);
                    softPwmWrite(this->pins.in4, this->speed.stopspeed);
                    break;
                default:
                    stop();
                    break;
            }      
    }
}

void CARRINHO::move_forward() {
    setMotor(motors::left_motor, directions::forward);
    setMotor(motors::right_motor, directions::forward);
}

void CARRINHO::move_backward() {
    setMotor(motors::left_motor, directions::backward);
    setMotor(motors::right_motor, directions::backward);
}

void CARRINHO::move_left() {
    setMotor(motors::left_motor, directions::left);
    setMotor(motors::right_motor, directions::left);
}

void CARRINHO::move_right() {
    setMotor(motors::left_motor, directions::right);
    setMotor(motors::right_motor, directions::right);
}

void CARRINHO::move_bottom_left() {
    setMotor(motors::left_motor, directions::bottom_left);
    setMotor(motors::right_motor, directions::bottom_left);
}

void CARRINHO::move_bottom_right() {
    setMotor(motors::left_motor, directions::bottom_right);
    setMotor(motors::right_motor, directions::bottom_right);
}

void CARRINHO::move_top_left() {
    setMotor(motors::left_motor, directions::top_left);
    setMotor(motors::right_motor, directions::top_left);
}

void CARRINHO::move_top_right() {
    setMotor(motors::left_motor, directions::top_right);
    setMotor(motors::right_motor, directions::top_right);
}