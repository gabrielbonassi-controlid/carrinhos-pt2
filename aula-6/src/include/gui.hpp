#include <cekeikon.h>


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


class GUI {
    public:
        GUI();
        ~GUI();

        static void on_mouse(int event, int c, int l, int flags, void* userdata);
        void paintButton(int button);
        void resetWindow();
        void putDigit(int& digit);
        void putMode(std::string mode);
        void showWindow();

        /*
         * Getters
         */
        Mat_<COR> getWindow(void);
        int getEstado(void);

        /*
         * Setters
         */
        void setWindow(Mat_<COR>& window);

    private:
        Mat_<COR> _window;
        static State _estado;
};