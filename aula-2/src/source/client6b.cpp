// client6b.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "client.hpp"

using namespace connection;

int main(int argc, char *argv[])
{
    if (argc != 2)
        erro("client6 servidorIpAddr\n");
    connection::CLIENT client(argv[1]);

    const int n = 100000;
    BYTE buf[n];
    client.receiveBytes(n, buf);
    if (client.testaBytes(buf, 111, n))
        printf("Recebeu corretamente %d bytes %d\n", n, 111);
    else
        printf("Erro na recepcao de %d bytes %d\n", n, 111);
    memset(buf, 214, n); // insere 214 em n bytes a partir do endereço buf
    client.sendBytes(n, buf);

    client.receiveBytes(n, buf);
    if (client.testaBytes(buf, 2, n))
        printf("Recebeu corretamente %d bytes %d\n", n, 2);
    else
        printf("Erro na recepcao de %d bytes %d\n", n, 2);
}

