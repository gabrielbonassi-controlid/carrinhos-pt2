// server1.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "server.hpp"
using namespace connection;

enum State {
    DEFAULT,
    DIAG_SUP_LEFT,
    UP,
    DIAG_SUP_RIGHT,
    LEFT_180,
    STOP,
    RIGHT_180,
    DIAG_INF_LEFT,
    DOWN,
    DIAG_INF_RIGHT
};

int main(int argc, char *argv[]) {
    connection::SERVER server;
    server.waitConnection();

    VideoCapture vi(1);
    vi.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    vi.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

    if (!vi.isOpened())
    {
        erro("Erro ao abrir a camera\n");
    }
    Mat_<COR> frame;
    uint32_t r, state;
    while (true) {
        server.receiveUint(r);
        server.receiveUint(state);

        if (r == 27) {
            exit(0);
        } else if (r == 1) {
            vi >> frame;
            if (frame.empty())
            {
                erro("Falha ao capturar frame\n");
            }

            // write state on frame
            putText(frame, to_string(state), Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, 16);
            server.sendImgComp(frame);
        }
    }
}