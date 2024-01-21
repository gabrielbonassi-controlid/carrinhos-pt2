// server.hpp
// Classe SERVER derivada da classe DEVICE
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#ifndef SERVER_HPP_
#define SERVER_HPP_
#include "device.hpp"

namespace connection {
class SERVER : public DEVICE
{
    const string PORT = "3490";         // the port users will be connecting to
    const int BACKLOG = 1;              // how many pending connections queue will hold
    int new_fd;                         // listen on sock_fd, new connection on new_fd
    int yes = 1;                        // for setsockopt() SO_REUSEADDR, below
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;

public:
    /*
     * Constructor
     */
    SERVER();

    /*
     * Destructor
     */
    ~SERVER();

    void waitConnection();

    void sendBytes(int nBytesToSend, BYTE *buf);

    void receiveBytes(int nBytesToReceive, BYTE *buf);
};
} // namespace conncection

#endif /* SERVER_HPP_ */