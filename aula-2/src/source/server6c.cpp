// server6c.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "server.hpp"
using namespace connection;

int main(void)
{
    connection::SERVER server;
    server.waitConnection();
    server.sendUint(1234567890);
    uint32_t u;
    server.receiveUint(u);
    cout << u << endl;
}