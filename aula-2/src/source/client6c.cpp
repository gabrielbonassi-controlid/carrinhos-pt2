// client6c.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "client.hpp"
using namespace connection;

int main(int argc, char *argv[])
{
    if (argc != 2)
        erro("client6c servidorIpAddr\n");
    connection::CLIENT client(argv[1]);
    uint32_t u;
    client.receiveUint(u);
    cout << u << endl;
    client.sendUint(3333333333);
}