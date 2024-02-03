#include "gui.hpp"

GUI::GUI() {
    _window = Mat_<COR>(240, 240, COR(128, 128, 128));
    resetWindow();
}

GUI::~GUI() {}

State GUI::_estado = DEFAULT;

void GUI::on_mouse(int event, int c, int l, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN) {
    if (0 <= l && l < 80 && 0 <= c && c < 80)
        _estado = DIAG_SUP_LEFT;
    else if (80 <= l && l < 160 && 0 <= c && c < 80)
        _estado = LEFT_180;
    else if (160 <= l && l < 240 && 0 <= c && c < 80)
        _estado = DIAG_INF_LEFT;
    else if (0 <= l && l < 80 && 80 <= c && c < 160)
        _estado = UP;
    else if (80 <= l && l < 160 && 80 <= c && c < 160)
        _estado = STOP;
    else if (160 <= l && l < 240 && 80 <= c && c < 160)
        _estado = DOWN;
    else if (0 <= l && l < 80 && 160 <= c && c < 240)
        _estado = DIAG_SUP_RIGHT;
    else if (80 <= l && l < 160 && 160 <= c && c < 240)
        _estado = RIGHT_180;
    else if (160 <= l && l < 240 && 160 <= c && c < 240)
        _estado = DIAG_INF_RIGHT;
    else
        _estado = DEFAULT;
    } else if (event == EVENT_LBUTTONUP) {
        _estado = DEFAULT;
    }
}

void GUI::paintButton() {
    COR red(0, 0, 255);
    switch (_estado) {
        case DIAG_SUP_LEFT:
            for (int l = 0; l < 80; l++)
                for (int c = 0; c < 80; c++)
                    _window(l, c) = red;
            break;
        case LEFT_180:
            for (int l = 80; l < 160; l++)
                for (int c = 0; c < 80; c++)
                    _window(l, c) = red;
            break;
        case DIAG_INF_LEFT:
            for (int l = 160; l < 240; l++)
                for (int c = 0; c < 80; c++)
                    _window(l, c) = red;
            break;
        case UP:
            for (int l = 0; l < 80; l++)
                for (int c = 80; c < 160; c++)
                    _window(l, c) = red;
            break;
        case STOP:
            for (int l = 80; l < 160; l++)
                for (int c = 80; c < 160; c++)
                    _window(l, c) = red;
            break;
        case DOWN:
            for (int l = 160; l < 240; l++)
                for (int c = 80; c < 160; c++)
                    _window(l, c) = red;
            break;
        case DIAG_SUP_RIGHT:
            for (int l = 0; l < 80; l++)
                for (int c = 160; c < 240; c++)
                    _window(l, c) = red;
            break;
        case RIGHT_180:
            for (int l = 80; l < 160; l++)
                for (int c = 160; c < 240; c++)
                    _window(l, c) = red;
            break;
        case DIAG_INF_RIGHT:
            for (int l = 160; l < 240; l++)
                for (int c = 160; c < 240; c++)
                    _window(l, c) = red;
            break;
        default:
            break;
    }
}

void GUI::resetWindow() {
    COR red(0, 0, 255);
    COR grey(128, 128, 128);

    _window.setTo(grey);
    reta(_window, 80, 0, 80, 240, COR(0, 0, 0), 2);
    reta(_window, 160, 0, 160, 240, COR(0, 0, 0), 2);
    reta(_window, 0, 80, 240, 80, COR(0, 0, 0), 2);
    reta(_window, 0, 160, 240, 160, COR(0, 0, 0), 2);

    // reta(_window, 120, 110, 120, 130, red, 2);
    // reta(_window, 110, 120, 130, 120, red, 2);

    flecha(_window, 60, 120, 20, 120, red, 2);   // CIMA
    flecha(_window, 180, 120, 220, 120, red, 2); // BAIXO
    flecha(_window, 120, 60, 120, 20, red, 2);   // ESQUERDA
    flecha(_window, 120, 180, 120, 220, red, 2); // DIREITA

    flecha(_window, 60, 60, 20, 20, red, 2);     // Diagonal CIMA/ESQUERDA
    flecha(_window, 60, 180, 20, 220, red, 2);   // diagonal CIMA/DIREITA
    flecha(_window, 180, 60, 220, 20, red, 2);   // Diagonal BAIXO/ESQUERDA
    flecha(_window, 180, 180, 220, 220, red, 2); // Diagonal BAIXO/DIREITA
}

void GUI::showWindow() {
    imshow("_window", _window);
}

Mat_<COR> GUI::getWindow() {
    return _window;
}

int GUI::getEstado() {
    return static_cast<int>(_estado);
}

void GUI::setWindow(Mat_<COR>& window) {
    _window = window;
}