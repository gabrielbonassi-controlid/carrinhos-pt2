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

// void CARRINHO::setMotor(int motor, int direction) {
//     switch (motor) {
//         case motors::left_motor:
//             switch (direction) {
//                 case directions::forward:
//                     std::cout << "left motor forward" << std::endl;
//                     softPwmWrite(motor::esq_frente, this->speed.fullspeed);
//                     softPwmWrite(motor::esq_tras, this->speed.stopspeed);
//                     break;
//                 case directions::backward:
//                 std::cout << "left motor backwards" << std::endl;
//                     softPwmWrite(motor::esq_frente, this->speed.stopspeed);
//                     softPwmWrite(motor::esq_tras, this->speed.fullspeed);
//                     break;
//                 case directions::brake:
//                     std::cout << "left motor brake" << std::endl;
//                     softPwmWrite(motor::esq_frente, speed::overdrive);
//                     softPwmWrite(motor::esq_tras, speed::overdrive);
//                     break;
//                 case directions::left:
//                     std::cout << "left motor left" << std::endl;
//                     softPwmWrite(motor::esq_frente, this->speed.fullspeed);
//                     softPwmWrite(motor::esq_tras, this->speed.stopspeed);
//                     break;
//                 case directions::right:
//                     std::cout << "left motor right" << std::endl;
//                     softPwmWrite(motor::esq_frente, this->speed.stopspeed);
//                     softPwmWrite(motor::esq_tras, this->speed.fullspeed);
//                     break;
//                 case directions::bottom_left:
//                     std::cout << "left motor bottom_left" << std::endl;
//                     softPwmWrite(motor::esq_frente, this->speed.stopspeed);
//                     softPwmWrite(motor::esq_tras, this->speed.fullspeed);
//                     break;
//                 case directions::bottom_right:
//                     std::cout << "left motor bottom_right" << std::endl;
//                     softPwmWrite(motor::esq_frente, this->speed.stopspeed);
//                     softPwmWrite(motor::esq_tras, this->speed.halfspeed);
//                     break;
//                 case directions::top_left:
//                     std::cout << "left motor top_left" << std::endl;
//                     softPwmWrite(motor::esq_frente, this->speed.fullspeed);
//                     softPwmWrite(motor::esq_tras, this->speed.stopspeed);
//                     break;
//                 case directions::top_right:
//                     std::cout << "left motor top_right" << std::endl;
//                     softPwmWrite(motor::esq_frente, this->speed.halfspeed);
//                     softPwmWrite(motor::esq_tras, this->speed.stopspeed);
//                     break;
//                 default:
//                     break;
//             }
//         case motors::right_motor:
//             switch (direction) {
//                 case directions::forward:
//                     std::cout << "right motor forward" << std::endl;
//                     softPwmWrite(motor::dir_frente, this->speed.fullspeed);
//                     softPwmWrite(motor::dir_tras, this->speed.stopspeed);
//                     break;
//                 case directions::backward:
//                     std::cout << "right motor forward" << std::endl;
//                     softPwmWrite(motor::dir_frente, this->speed.stopspeed);
//                     softPwmWrite(motor::dir_tras, this->speed.fullspeed);
//                     break;
//                 case directions::brake:
//                     std::cout << "right motor forward" << std::endl;
//                     softPwmWrite(motor::dir_frente, speed::overdrive);
//                     softPwmWrite(motor::dir_tras, speed::overdrive);
//                     break;
//                 case directions::left:
//                     std::cout << "right motor forward" << std::endl;
//                     softPwmWrite(motor::dir_frente, this->speed.stopspeed);
//                     softPwmWrite(motor::dir_tras, this->speed.fullspeed);
//                     break;
//                 case directions::right:
//                     softPwmWrite(motor::dir_frente, this->speed.fullspeed);
//                     softPwmWrite(motor::dir_tras, this->speed.stopspeed);
//                     break;
//                 case directions::bottom_left:
//                     softPwmWrite(motor::dir_frente, this->speed.stopspeed);
//                     softPwmWrite(motor::dir_tras, this->speed.halfspeed);
//                     break;
//                 case directions::bottom_right:
//                     softPwmWrite(motor::dir_frente, this->speed.stopspeed);
//                     softPwmWrite(motor::dir_tras, this->speed.fullspeed);
//                     break;
//                 case directions::top_left:
//                     softPwmWrite(motor::dir_frente, this->speed.halfspeed);
//                     softPwmWrite(motor::dir_tras, this->speed.stopspeed);
//                     break;
//                 case directions::top_right:
//                     softPwmWrite(motor::dir_frente, this->speed.fullspeed);
//                     softPwmWrite(motor::dir_tras, this->speed.stopspeed);
//                     break;
//                 default:
//                     break;
//             }      
//     }
// }

void CARRINHO::move_forward() {
    // setMotor(motors::left_motor, directions::forward);
    // setMotor(motors::right_motor, directions::forward);
    softPwmWrite(motor::esq_frente, speed::fullspeed);
    softPwmWrite(motor::esq_tras, speed::stopspeed);
    softPwmWrite(motor::dir_frente, speed::fullspeed);
    softPwmWrite(motor::dir_tras, speed::stopspeed);
}

void CARRINHO::move_backward() {
    // setMotor(motors::left_motor, directions::backward);
    // setMotor(motors::right_motor, directions::backward);
    softPwmWrite(motor::esq_frente, speed::stopspeed);
    softPwmWrite(motor::esq_tras, speed::fullspeed);
    softPwmWrite(motor::dir_frente, speed::stopspeed);
    softPwmWrite(motor::dir_tras, speed::fullspeed);
}

void CARRINHO::move_left() {
    // setMotor(motors::left_motor, directions::left);
    // setMotor(motors::right_motor, directions::left);
    softPwmWrite(motor::esq_frente, speed::fullspeed);
    softPwmWrite(motor::esq_tras, speed::stopspeed);
    softPwmWrite(motor::dir_frente, speed::stopspeed);
    softPwmWrite(motor::dir_tras, speed::fullspeed);
}

void CARRINHO::move_right() {
    // setMotor(motors::left_motor, directions::right);
    // setMotor(motors::right_motor, directions::right);
    softPwmWrite(motor::esq_frente, speed::stopspeed);
    softPwmWrite(motor::esq_tras, speed::fullspeed);
    softPwmWrite(motor::dir_frente, speed::fullspeed);
    softPwmWrite(motor::dir_tras, speed::stopspeed);
}

void CARRINHO::move_bottom_left() {
    softPwmWrite(motor::esq_frente, speed::stopspeed);
    softPwmWrite(motor::esq_tras, speed::fullspeed);
    softPwmWrite(motor::dir_frente, speed::stopspeed);
    softPwmWrite(motor::dir_tras, speed::halfspeed);
}

void CARRINHO::move_bottom_right() {
    // setMotor(motors::left_motor, directions::bottom_right);
    // setMotor(motors::right_motor, directions::bottom_right);
    softPwmWrite(motor::esq_frente, speed::stopspeed);
    softPwmWrite(motor::esq_tras, speed::halfspeed);
    softPwmWrite(motor::dir_frente, speed::stopspeed);
    softPwmWrite(motor::dir_tras, speed::fullspeed);
}

void CARRINHO::move_top_left() {
    // setMotor(motors::left_motor, directions::top_left);
    // setMotor(motors::right_motor, directions::top_left);
    softPwmWrite(motor::esq_frente, speed::fullspeed);
    softPwmWrite(motor::esq_tras, speed::stopspeed);
    softPwmWrite(motor::dir_frente, speed::halfspeed);
    softPwmWrite(motor::dir_tras, speed::stopspeed);
}

void CARRINHO::move_top_right() {
    // setMotor(motors::left_motor, directions::top_right);
    // setMotor(motors::right_motor, directions::top_right);
    softPwmWrite(motor::esq_frente, speed::halfspeed);
    softPwmWrite(motor::esq_tras, speed::stopspeed);
    softPwmWrite(motor::dir_frente, speed::fullspeed);
    softPwmWrite(motor::dir_tras, speed::stopspeed);
}