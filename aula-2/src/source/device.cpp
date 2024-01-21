// device.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "device.hpp"

using namespace connection;

void * DEVICE::get_in_addr(struct sockaddr *sa) {
        if (sa->sa_family == AF_INET)
        {
            return &(((struct sockaddr_in *)sa)->sin_addr);
        }
        return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void DEVICE::sendUint(uint32_t m) {
        m = htonl(m);
        sendBytes(sizeof(uint32_t), (BYTE *)&m);
}

void DEVICE::sendVb(const vector<BYTE> &vb) {
        sendUint(vb.size());
        sendBytes(vb.size(), (BYTE *)vb.data());
}

void DEVICE::receiveUint(uint32_t &m) {
        receiveBytes(sizeof(uint32_t), (BYTE *)&m);
        m = ntohl(m);
}

void DEVICE::receiveVb(vector<BYTE> &vb) {
        uint32_t size;
        receiveUint(size);

        vb.resize(size);

        receiveBytes(size, vb.data());
}

bool DEVICE::testaBytes(BYTE *buf, BYTE b, int n)
{
    // Testa se n bytes da memoria buf possuem valor b
    bool igual = true;
    for (unsigned i = 0; i < n; i++)
        if (buf[i] != b)
        {
            igual = false;
            break;
        }
    return igual;
}

bool DEVICE::testaVb(const vector<BYTE> vb, BYTE b)
{
    // Testa se todos os bytes de vb possuem valor b
    bool igual = true;
    for (unsigned i = 0; i < vb.size(); i++)
        if (vb[i] != b)
        {
            igual = false;
            break;
        }
    return igual;
}