#include "server.hpp"
#include "carrinho.hpp"

using namespace std;
using namespace connection;

enum States {
    IDLE,
    DETECT_BOX,
    STOP_DETECTED,
    READ_DIGIT,
    EXEC_DIGIT,
    STOP_FINISHED,
    EXIT
};

enum Commands {
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

// int fsm(int last_state, bool start, CARRINHO carro, int count[10], int curr_digit, TimePoint& t, bool& finished, bool& recognized) {
//     switch (last_state) {
//         case IDLE:
//             if (start) {
//                 carro.stop();
//                 finished = true;
//                 return DETECT_BOX;
//             }
//             break;
//         case DETECT_BOX:
//             std::cout << "seguindo placa" << std::endl
//             if (recognized) {
//                 carro.move_forward(t, finished);
//                 return STOP_DETECTED;
//             }
//             break;
//         case STOP_DETECTED:
//             carro.stop();
//             if (finished) {
//                 return READ_DIGIT;
//             }
//             break;
//         case READ_DIGIT:
//             std::cout << "reconhecendo digito" << std::endl;

//             break;
//         case EXEC_DIGIT:
//             break;
//         case STOP_FINISHED:
//             break;
//         case EXIT:
//             break;
//     }

// }

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
    uint32_t command, ch;
    uint32_t digit = 0;
    uint32_t mode = 2;
    uint32_t received = 0;
    Mat_<COR> frame;
    bool finished = true;
    // TimePoint t1;
    std::chrono::high_resolution_clock::time_point t1;
    uint32_t digit_copy;


    do {
        vi >> frame;
        server.sendImgComp(frame);
        // while (received == 0) {
        //     server.receiveUint(received);
        // }
        server.receiveUint(received);
        server.receiveUint(ch);
        received = 0;
        server.receiveUint(mode);
        if (mode == 1) { // automático
            std::cout << "Modo automático" << std::endl;
            server.receiveUint(digit);
            std::cout << "Dígito recebido: " << digit << std::endl;
            if (finished) {
                finished = false;
                std::cout << "Começando um comando" << std::endl;
                digit_copy = digit;
                t1 = std::chrono::high_resolution_clock::now();
                if (digit == 0 || digit == 1) {
                    carrinho.stop();
                } else if (digit == 2) {
                    carrinho.turn180left(t1, finished);
                } else if (digit == 3) {
                    carrinho.turn180right(t1, finished);
                } else if (digit == 4 || digit == 5) {
                    carrinho.move_under(t1, finished);
                } else if (digit == 6 || digit == 7) {
                    carrinho.turn90left(t1, finished);
                } else if (digit == 8 || digit == 9) {
                    carrinho.turn90right(t1, finished);
                } else {
                    carrinho.stop();
                }
            } else {
                std::cout << "Ainda não acabou" << std::endl;
                if (digit_copy == 0 || digit_copy == 1) {
                    carrinho.stop();
                } else if (digit_copy == 2) {
                    carrinho.turn180left(t1, finished);
                } else if (digit_copy == 3) {
                    carrinho.turn180right(t1, finished);
                } else if (digit_copy == 4 || digit_copy == 5) {
                    carrinho.move_under(t1, finished);
                } else if (digit_copy == 6 || digit_copy == 7) {
                    carrinho.turn90left(t1, finished);
                } else if (digit_copy == 8 || digit_copy == 9) {
                    carrinho.turn90right(t1, finished);
                } else {
                    carrinho.stop();
                }
            }
            // server.sendUint(static_cast<uint32_t>(finished));
        } else if (mode == 2) { //manual
            server.receiveUint(command);
            if (command >= static_cast<uint32_t>(Commands::DEFAULT) && command <= static_cast<uint32_t>(Commands::DIAG_INF_RIGHT)) {
                std::cout << "State: " << command << std::endl;
                switch (static_cast<Commands>(command)) {
                case UP:
                    std::cout << "Pra frente" << std::endl;
                    carrinho.move_forward();
                    break;
                case DOWN:
                    std::cout << "Pra trás" << std::endl;
                    carrinho.move_backward();
                    break;
                case LEFT_180:
                    std::cout << "Pra esquerda" << std::endl;
                    carrinho.move_left();
                    break;
                case RIGHT_180:
                    std::cout << "Pra direita" << std::endl;
                    carrinho.move_right();
                    break;
                case STOP:
                    std::cout << "Para" << std::endl;
                    carrinho.stop();
                    break;
                case DIAG_SUP_LEFT:
                    std::cout << "Pra frente diagonal esquerda" << std::endl;
                    carrinho.move_top_left();
                    break;
                case DIAG_SUP_RIGHT:
                    std::cout << "Pra frente diagonal direita" << std::endl;
                    carrinho.move_top_right();
                    break;
                case DIAG_INF_LEFT:
                    std::cout << "Pra trás diagonal esquerda" << std::endl;
                    carrinho.move_bottom_left();
                    break;
                case DIAG_INF_RIGHT:
                    std::cout << "Pra trás diagonal direita" << std::endl;
                    carrinho.move_bottom_right();
                    break;
                case DEFAULT:
                    std::cout << "Default" << std::endl;
                    carrinho.stop();
                    break;
                default:
                    break;
                }
            }
        }
    } while (ch != 27);
}