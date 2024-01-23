// server.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "server.hpp"

using namespace connection;

SERVER::SERVER() {
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    // error checking
    rv = getaddrinfo(NULL, PORT.c_str(), &hints, &servinfo);
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
            perror("server: socket");
            continue;
        }

        // bind socket to port
        rv = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        if (rv == -1)
        {
            perror("setsockopt");
            exit(1);
        }
        rv = bind(sockfd, p->ai_addr, p->ai_addrlen);
        if (rv == -1)
        {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        // conncection made
        break;
    }

    // error checking
    if (p == NULL)
    {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }
    freeaddrinfo(servinfo);

    // listen for connections
    rv = listen(sockfd, BACKLOG);
    if (rv == -1)
    {
        perror("listen");
        exit(1);
    }
}

SERVER::~SERVER() {
    close(new_fd);
    close(sockfd);
}

void SERVER::waitConnection() {
    printf("server: waiting for connections...\n");
    while (1)
    {
        sin_size = sizeof their_addr;

        // cast to sockaddr
        struct sockaddr *addr = (struct sockaddr *)&their_addr;

        new_fd = accept(sockfd, addr, &sin_size);
        if (new_fd == -1)
        {
            perror("accept");
            continue;
        }
        else
        {
            printf("Connection accepted\n");
            inet_ntop(their_addr.ss_family, get_in_addr(addr), s, sizeof(s));
            printf("server: got connection from %s\n", s);

            // close socket so that no more connections can be made
            close(sockfd);
            break;
        }
    }
}

void SERVER::sendBytes(int nBytesToSend, BYTE *buf) {
    while (nBytesToSend > 0)
    {
        rv = send(new_fd, buf, nBytesToSend, 0);
        if (rv == -1)
        {
            perror("send");
            exit(1);
        }
        nBytesToSend -= rv;
        buf += rv;
    }
}

void SERVER::receiveBytes(int nBytesToReceive, BYTE *buf) {
    while (nBytesToReceive > 0)
    {
        rv = recv(new_fd, buf, nBytesToReceive, 0);
        if (rv == -1)
        {
            perror("recv");
            exit(1);
        }
        nBytesToReceive -= rv;
        buf += rv;
    }
}