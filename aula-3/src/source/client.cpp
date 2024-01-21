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