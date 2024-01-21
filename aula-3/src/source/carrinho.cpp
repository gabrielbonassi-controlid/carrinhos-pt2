// carrinho.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "carrinho.hpp"

CARRINHO::CARRINHO()
{
    wiringPiSetup();
    if (softPwmCreate(pins.in1, 0, 100))
        erro("ERRO PIN3\n");
    if (softPwmCreate(pins.in2, 0, 100))
        erro("ERRO PIN4\n");
    if (softPwmCreate(pins.in3, 0, 100))
        erro("ERRO PIN9\n");
    if (softPwmCreate(pins.in4, 0, 100))
        erro("ERRO PIN12\n");
}

CARRINHO::~CARRINHO()
{
    stop();
}

void CARRINHO::stop()
{
    softPwmWrite(pins.in1, speed.stop);
    softPwmWrite(pins.in2, speed.stop);
    softPwmWrite(pins.in3, speed.stop);
    softPwmWrite(pins.in4, speed.stop);
    digitalWrite(pins.in1, LOW);
    digitalWrite(pins.in2, LOW);
    digitalWrite(pins.in3, LOW);
    digitalWrite(pins.in4, LOW);
}

void CARRINHO::setMotor(s_motors& motor, s_directions& direction) {
    switch (motor) {
        case motors.left:
            switch (direction) {
                case directions.forward:
                    softPwmWrite(pins.in1, speed.overdrive);
                    softPwmWrite(pins.in2, speed.stop);
                    break;
                case directions.backward:
                    softPwmWrite(pins.in1, speed.stop);
                    softPwmWrite(pins.in2, speed.fullspeed);
                    break;
                case directions.stop:
                    softPwmWrite(pins.in1, speed.overdrive);
                    softPwmWrite(pins.in2, speed.overdrive);
                    break;
                case directions.left:
                    softPwmWrite(pins.in1, speed.fullspeed);
                    softPwmWrite(pins.in2, speed.stop);
                    break;
                case directions.right:
                    softPwmWrite(pins.in1, speed.stop);
                    softPwmWrite(pins.in2, speed.fullspeed);
                    break;
                case directions.bottom_left:
                    softPwmWrite(pins.in1, speed.stop);
                    softPwmWrite(pins.in2, speed.fullspeed);
                    break;
                case directions.bottom_right:
                    softPwmWrite(pins.in1, speed.stop);
                    softPwmWrite(pins.in2, speed.halfspeed);
                    break;
                case directions.top_left:
                    softPwmWrite(pins.in1, speed.fullspeed);
                    softPwmWrite(pins.in2, speed.stop);
                    break;
                case directions.top_right:
                    softPwmWrite(pins.in1, speed.halfspeed);
                    softPwmWrite(pins.in2, speed.stop);
                    break;
                default:
                    stop();
                    break;
            }
        case motors.right:
            switch (direction) {
                case directions.forward:
                    softPwmWrite(pins.in3, speed.overdrive);
                    softPwmWrite(pins.in4, speed.stop);
                    break;
                case directions.backward:
                    softPwmWrite(pins.in3, speed.stop);
                    softPwmWrite(pins.in4, speed.fullspeed);
                    break;
                case directions.stop:
                    softPwmWrite(pins.in3, speed.overdrive);
                    softPwmWrite(pins.in4, speed.overdrive);
                    break;
                case directions.left:
                    softPwmWrite(pins.in3, speed.stop);
                    softPwmWrite(pins.in4, speed.fullspeed);
                    break;
                case directions.right:
                    softPwmWrite(pins.in3, speed.fullspeed);
                    softPwmWrite(pins.in4, speed.stop);
                    break;
                case directions.bottom_left:
                    softPwmWrite(pins.in3, speed.stop);
                    softPwmWrite(pins.in4, speed.halfspeed);
                    break;
                case directions.bottom_right:
                    softPwmWrite(pins.in3, speed.stop);
                    softPwmWrite(pins.in4, speed.fullspeed);
                    break;
                case directions.top_left:
                    softPwmWrite(pins.in3, speed.halfspeed);
                    softPwmWrite(pins.in4, speed.stop);
                    break;
                case directions.top_right:
                    softPwmWrite(pins.in3, speed.fullspeed);
                    softPwmWrite(pins.in4, speed.stop);
                    break;
                default:
                    stop();
                    break;
            }      
    }
}

void forward() {
    setMotor(motors.left, directions.forward);
    setMotor(motors.right, directions.forward);
}

void backward() {
    setMotor(motors.left, directions.backward);
    setMotor(motors.right, directions.backward);
}

void left() {
    setMotor(motors.left, directions.left);
    setMotor(motors.right, directions.left);
}

void right() {
    setMotor(motors.left, directions.right);
    setMotor(motors.right, directions.right);
}

void bottom_left() {
    setMotor(motors.left, directions.bottom_left);
    setMotor(motors.right, directions.bottom_left);
}

void bottom_right() {
    setMotor(motors.left, directions.bottom_right);
    setMotor(motors.right, directions.bottom_right);
}

void top_left() {
    setMotor(motors.left, directions.top_left);
    setMotor(motors.right, directions.top_left);
}

void top_right() {
    setMotor(motors.left, directions.top_right);
    setMotor(motors.right, directions.top_right);
}