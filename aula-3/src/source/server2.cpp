// server1.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "server.hpp"
#include "carrinho.hpp"
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
    CARRINHO carrinho;
    server.waitConnection();

    VideoCapture vi(1);
    vi.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    vi.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

    if (!vi.isOpened())
    {
        erro("Erro ao abrir a camera\n");
    }
    Mat_<COR> frame;
    uint32_t r, state = 0;
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
            server.sendImgComp(frame);

            if (state >= static_cast<uint32_t>(State::DEFAULT) && state <= static_cast<uint32_t>(State::DIAG_INF_RIGHT)) {
                switch (static_cast<State>(state)) {
                case UP:
                    carrinho.move_forward();
                    break;
                case DOWN:
                    carrinho.move_backward();
                    break;
                case LEFT_180:
                    carrinho.move_left();
                    break;
                case RIGHT_180:
                    carrinho.move_right();
                    break;
                case STOP:
                    carrinho.stop();
                    break;
                case DIAG_SUP_LEFT:
                    carrinho.move_top_left();
                    break;
                case DIAG_SUP_RIGHT:
                    carrinho.move_top_right();
                    break;
                case DIAG_INF_LEFT:
                    carrinho.move_bottom_left();
                    break;
                case DIAG_INF_RIGHT:
                    carrinho.move_bottom_right();
                    break;
                default:
                    carrinho.stop();
                    break;
                }
            } else {
                carrinho.stop();
            }
        }
    }
}