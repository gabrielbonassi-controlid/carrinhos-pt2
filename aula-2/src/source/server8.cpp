// server8.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "server.hpp"
using namespace connection;

int main(void)
{
    connection::SERVER server;
    server.waitConnection();
    vector<BYTE> vb;

    vb.assign(100000, 111);
    server.sendVb(vb);
    server.receiveVb(vb);
    if (server.testaVb(vb, 222))
        printf("Recebi corretamente %lu bytes %u\n", vb.size(), 222);
    else
        printf("Erro na recepcao de %lu bytes %u\n", vb.size(), 222);
    vb.assign(100000, 2);
    server.sendVb(vb);
}