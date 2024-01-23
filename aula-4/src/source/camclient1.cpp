// camclient1.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "client.hpp"

using namespace connection;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        erro("client hostname\n");
    }

    connection::CLIENT client(argv[1]);

    Mat_<COR> frame;
    uint32_t key;

    namedWindow("OrangePi Live Feed");
    while (true)
    {
        key = waitKey(30);
        if (key == 27)
        {
            client.sendUint(115);
            break;
        }

        client.sendUint(0);
        client.receiveImg(frame);
        imshow("OrangePi Live Feed", frame);

        if (frame.empty())
        {
            erro("Falha ao receber frame\n");
        }
    }
}