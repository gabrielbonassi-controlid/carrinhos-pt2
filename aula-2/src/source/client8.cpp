// client8.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "client.hpp"
using namespace connection;

int main(int argc, char *argv[])
{
    if (argc != 2)
        erro("client6 servidorIpAddr\n");
    connection::CLIENT client(argv[1]);
    vector<BYTE> vb;
    client.receiveVb(vb);
    if (client.testaVb(vb, 111))
        printf("Recebi corretamente %lu bytes %u\n", vb.size(), 111);
    else
        printf("Erro na recepcao de %lu bytes %u\n", vb.size(), 111);
    vb.assign(100000, 222);
    client.sendVb(vb);

    client.receiveVb(vb);
    if (client.testaVb(vb, 1))
        printf("Recebi corretamente %lu bytes %u\n", vb.size(), 1);
    else
        printf("Erro na recepcao de %lu bytes %u\n", vb.size(), 1);
}