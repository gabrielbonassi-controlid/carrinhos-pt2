// client.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "client.hpp"

using namespace connection;

CLIENT::CLIENT(string endereco) {
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    endereco.copy(s, endereco.size());

    // error checking
    rv = getaddrinfo(endereco.c_str(), PORT.c_str(), &hints, &servinfo);
    if (rv != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(1);
    }

    // make connection
    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        // create socket
        sockfd = socket(p->ai_family, p->ai_socktype,
                        p->ai_protocol);
        if (sockfd == -1)
        {
            perror("client: socket");
            continue;
        }

        // connect to server
        rv = connect(sockfd, p->ai_addr, p->ai_addrlen);
        if (rv == -1)
        {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        // connection made
        break;
    }

    // error checking
    if (p == NULL)
    {
        fprintf(stderr, "client: failed to connect\n");
        exit(1);
    }
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);

    printf("client: connecting to %s\n", s);
    freeaddrinfo(servinfo);
}

CLIENT::~CLIENT() {
    close(sockfd);
}

void CLIENT::sendBytes(int nBytesToSend, BYTE *buf) {
    while (nBytesToSend > 0)
        {
            rv = send(sockfd, buf, nBytesToSend, 0);
            if (rv == -1)
            {
                perror("send");
                exit(1);
            }
            nBytesToSend -= rv;
            buf += rv;
        }
}

void CLIENT::receiveBytes(int nBytesToReceive, BYTE *buf) {
    while (nBytesToReceive > 0)
        {
            rv = recv(sockfd, buf, nBytesToReceive, 0);
            if (rv == -1)
            {
                perror("recv");
                exit(1);
            }
            nBytesToReceive -= rv;
            buf += rv;
        }
}

void CLIENT::resetJanela(Mat_<COR> janela) {
    COR cinza(128, 128, 128);
    COR vermelho(0, 0, 255);
    janela.setTo(cinza);
    reta(janela, 80, 0, 80, 240, COR(0, 0, 0), 2);
    reta(janela, 160, 0, 160, 240, COR(0, 0, 0), 2);
    reta(janela, 0, 80, 240, 80, COR(0, 0, 0), 2);
    reta(janela, 0, 160, 240, 160, COR(0, 0, 0), 2);

    reta(janela, 120, 110, 120, 130, vermelho, 2);
    reta(janela, 110, 120, 130, 120, vermelho, 2);

    flecha(janela, 60, 120, 20, 120, vermelho, 2);   // CIMA
    flecha(janela, 180, 120, 220, 120, vermelho, 2); // BAIXO
    flecha(janela, 120, 60, 120, 20, vermelho, 2);   // ESQUERDA
    flecha(janela, 120, 180, 120, 220, vermelho, 2); // DIREITA

    flecha(janela, 60, 60, 20, 20, vermelho, 2);     // Diagonal CIMA/ESQUERDA
    flecha(janela, 60, 180, 20, 220, vermelho, 2);   // diagonal CIMA/DIREITA
    flecha(janela, 180, 60, 220, 20, vermelho, 2);   // Diagonal BAIXO/ESQUERDA
    flecha(janela, 180, 180, 220, 220, vermelho, 2); // Diagonal BAIXO/DIREITA
}