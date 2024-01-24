#include "server.hpp"
#include "carrinho.hpp"

using namespace std;
using namespace connection;

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
    uint32_t dist, positive, ch;
    uint32_t received = 0;
    do {
        vi >> frame;
        server.sendImgComp(frame);
        while (received != 0) {
            server.receiveUint(received);
        }
        server.receiveUint(ch);
        received = 0;
        server.receiveUint(dist);
        server.receiveUint(positive);
        carrinho.move_forward(dist, static_cast<bool>(positive));

    } while (ch != 27);
}