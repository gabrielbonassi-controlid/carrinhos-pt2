// server6b.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "server.hpp"

using namespace connection;
int main(void)
{
    connection::SERVER server;
    server.waitConnection();

    const int n = 100000;
    BYTE buf[n];
    memset(buf, 111, n); // insere 111 em n bytes a partir do endereço buf
    server.sendBytes(n, buf);
    server.receiveBytes(n, buf);
    if (server.testaBytes(buf, 214, n))
        printf("Recebeu corretamente %d bytes %d\n", n, 214);
    else
        printf("Erro na recepcao de %d bytes %d\n", n, 214);
    memset(buf, 111, n);
    server.sendBytes(n, buf);
}