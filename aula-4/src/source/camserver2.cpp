// camserver2.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "server.hpp"

using namespace connection;

int main(int argc, char *argv[])
{

    connection::SERVER server;
    server.waitConnection();

    bool finished = false;

    VideoCapture vi(1);
    vi.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    vi.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

    if (!vi.isOpened())
    {
        erro("Erro ao abrir a camera\n");
    }

    Mat_<COR> frame;
    uint32_t r;

    while (true)
    {
        // uso de uint8 para reduzir o atraso

        while (r != 0)
        {
            server.receiveUint(r);

            if ((char)r == 's')
            {
                break;
            }
        }

        vi >> frame;

        if (frame.empty())
        {
            erro("Falha ao capturar frame\n");
        }

        server.sendImgComp(frame);
    }

    return 0;
}