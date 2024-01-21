// device.hpp
// Classe DEVICE
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#ifndef DEVICE_HPP_
#define DEVICE_HPP_

#include <cekeikon.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#define MAXDATASIZE 100 // max number of bytes we can get at once

namespace connection {
class DEVICE
{
protected:
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int sockfd, numbytes;
    char s[INET6_ADDRSTRLEN];
    void *get_in_addr(struct sockaddr *sa);

public:
    virtual void sendBytes(int nBytesToSend, BYTE *buf) = 0;

    virtual void receiveBytes(int nBytesToReceive, BYTE *buf) = 0;
    
    void sendUint(uint32_t m);
    
    void sendVb(const vector<BYTE> &vb);
    
    void sendImg(const Mat_<COR> &img);
    
    void sendImgComp(const Mat_<COR> &img);
    
    void receiveUint(uint32_t &m);
    
    void receiveVb(vector<BYTE> &vb);
    
    void receiveImg(Mat_<COR> &img);
    
    void receiveImgComp(Mat_<COR> &img);

    static bool testaBytes(BYTE *buf, BYTE b, int n);

    static bool testaVb(const vector<BYTE> vb, BYTE b);
};

} // namespace connection

#endif // DEVICE_HPP_