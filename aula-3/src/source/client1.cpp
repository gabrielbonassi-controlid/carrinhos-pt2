// client1.cpp
// Aluno 1: Gabriel Lujan Bonassi - NUSP: 11256816
// Aluno 2: Luís Henrique de Almeida Fernandes - 11820030
#include "client.hpp"
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

State estado = DEFAULT;
void on_mouse(int event, int c, int l, int flags, void* userdata) { //Funcao callback
    if (event == EVENT_LBUTTONDOWN) {
    if (0 <= l && l < 80 && 0 <= c && c < 80)
        estado = DIAG_SUP_LEFT;
    else if (80 <= l && l < 160 && 0 <= c && c < 80)
        estado = UP;
    else if (120 <= l && l < 240 && 0 <= c && c < 80)
        estado = DIAG_SUP_RIGHT;
    else if (0 <= l && l < 80 && 80 <= c && c < 160)
        estado = LEFT_180;
    else if (80 <= l && l < 160 && 80 <= c && c < 160)
        estado = STOP;
    else if (120 <= l && l < 240 && 80 <= c && c < 160)
        estado = RIGHT_180;
    else if (0 <= l && l < 80 && 160 <= c && c < 240)
        estado = DIAG_INF_LEFT;
    else if (80 <= l && l < 160 && 160 <= c && c < 240)
        estado = DOWN;
    else if (120 <= l && l < 240 && 160 <= c && c < 240)
        estado = DIAG_INF_RIGHT;
    else
        estado = DEFAULT;
    } else if (event == EVENT_LBUTTONUP) {
        estado = DEFAULT;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Uso: client1 <ip>\n");
    }
    // ### SETUP DA JANELA ###
    COR cinza(128, 128, 128);
    COR vermelho(0, 0, 255);
    Mat_<COR> janela(240, 240, cinza);
    namedWindow("janela");
    setMouseCallback("janela", on_mouse);

    // ### SETUP DA TRANSMISSÃO ###
    connection::CLIENT client(argv[1]);
    Mat_<COR> image; // feed do orangepi
    Mat_<COR> screen; // tela total
    bool recording = false; // se deve gerar arquivo de gravação
    std::string name = "";
    if (argc == 3) {
        recording = true;
        name = argv[2];
    }
    VideoWriter vo(name, CV_FOURCC('X', 'V', 'I', 'D'), 30, Size(320, 240));
    int ch;
    reta(janela, 80, 0, 80, 240, COR(0, 0, 0));
    reta(janela, 160, 0, 160, 240, COR(0, 0, 0));
    reta(janela, 0, 80, 240, 80, COR(0, 0, 0));
    reta(janela, 0, 160, 240, 160, COR(0, 0, 0));

    reta(janela, 120, 110, 120, 130, vermelho);
    reta(janela, 110, 120, 130, 120, vermelho);

    flecha(janela, 60, 120, 20, 120, vermelho);   // CIMA
    flecha(janela, 180, 120, 220, 120, vermelho); // BAIXO
    flecha(janela, 120, 60, 120, 20, vermelho);   // ESQUERDA
    flecha(janela, 120, 180, 120, 220, vermelho); // DIREITA

    flecha(janela, 60, 60, 20, 20, vermelho);     // Diagonal CIMA/ESQUERDA
    flecha(janela, 60, 180, 20, 220, vermelho);   // diagonal CIMA/DIREITA
    flecha(janela, 180, 60, 220, 20, vermelho);   // Diagonal BAIXO/ESQUERDA
    flecha(janela, 180, 180, 220, 220, vermelho); // Diagonal BAIXO/DIREITA

    uint32_t key;
    while (true) {
        key = waitKey(30);

        if (key == 27) {
            client.sendUint(27);
            exit(0);
        }
        client.sendUint(1); //READY
        client.sendUint(static_cast<uint32_t>(estado));
        client.receiveImgComp(image);

        janela.setTo(cinza);
        switch (estado) {
            case DIAG_SUP_LEFT:
                for (int l = 0; l < 80; l++)
                    for (int c = 0; c < 80; c++)
                        janela(l, c) = vermelho;
                break;
            case UP:
                for (int l = 80; l < 160; l++)
                    for (int c = 0; c < 80; c++)
                        janela(l, c) = vermelho;
                break;
            case DIAG_SUP_RIGHT:
                for (int l = 120; l < 240; l++)
                    for (int c = 0; c < 80; c++)
                        janela(l, c) = vermelho;
                break;
            case LEFT_180:
                for (int l = 0; l < 80; l++)
                    for (int c = 80; c < 160; c++)
                        janela(l, c) = vermelho;
                break;
            case STOP:
                for (int l = 80; l < 160; l++)
                    for (int c = 80; c < 160; c++)
                        janela(l, c) = vermelho;
                break;
            case RIGHT_180:
                for (int l = 120; l < 240; l++)
                    for (int c = 80; c < 160; c++)
                        janela(l, c) = vermelho;
                break;
            case DIAG_INF_LEFT:
                for (int l = 0; l < 80; l++)
                    for (int c = 160; c < 240; c++)
                        janela(l, c) = vermelho;
                break;
            case DOWN:
                for (int l = 80; l < 160; l++)
                    for (int c = 160; c < 240; c++)
                        janela(l, c) = vermelho;
                break;
            case DIAG_INF_RIGHT:
                for (int l = 120; l < 240; l++)
                    for (int c = 160; c < 240; c++)
                        janela(l, c) = vermelho;
                break;
            default:
                break;
        }

        screen = grudaH(janela, image, 0, cinza);
        imshow("janela", screen);
        //client.sendUint(1) // confirma recebimento da imagem
        if (recording) {
            if (argc == 4) {
                if (argv[3][0] == 't')
                    vo << screen;
                else if (argv[3][0] == 'c')
                    vo << frame;
            }
        }
    }
}