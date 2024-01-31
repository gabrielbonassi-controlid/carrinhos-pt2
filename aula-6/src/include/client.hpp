// client.hpp
// Classe CLIENT derivada da classe DEVICE
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#ifndef CLIENT_HPP_
#define CLIENT_HPP_
#include "device.hpp"

namespace connection {
class CLIENT : public DEVICE
{
    const string PORT = "3490"; // the port client will be connecting to

public:
    /*
     * Constructor
     */
    CLIENT(string endereco);

    /*
     * Destructor
     */
    ~CLIENT();

    void sendBytes(int nBytesToSend, BYTE *buf);

    void receiveBytes(int nBytesToReceive, BYTE *buf);

    void resetJanela(Mat_<COR> janela);

};

} // namespace connection
#endif /* CLIENT_HPP_ */