#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include "client.hpp"

using namespace std;
using namespace connection;

enum State {
    FOLLOW,
    STOP
};

struct MIN_MAX_MATCH {
    double min_val;
    double max_val;
    Point min_loc;
    Point max_loc;
    Point match_loc;
    Point last_loc;
};

MIN_MAX_MATCH min_max;
MIN_MAX_MATCH min_max_normed;

Mat_<FLT> result;
Mat_<FLT> result_normed;

int bestTemplateSize(int last_size, Mat_<FLT> img_ref, Mat_<FLT> next_frame_flt) {
    int size;
    int min = 50;
    int max = 100;
    float max_value_aux = 0.0;
    Mat_<FLT> img_ref_temp;

    if (last_size < 15) {
        min = 15;
        max = 60;
    } else {
        min = last_size - 10;
        max = last_size + 10;
    }
    
#pragma omp parallel for
    for (int i = min; i < max; i = i + 5) {
        cv::Mat img_ref_temp, result;
        double max_value_aux_par = -1;
        int size_aux = -1;

        resize(img_ref, img_ref_temp, Size(i, i), 0, 0, INTER_AREA);
        img_ref_temp = somaAbsDois(dcReject(img_ref_temp, 1.0));
        matchTemplate(next_frame_flt, img_ref_temp, result, CV_TM_CCOEFF_NORMED);

        MIN_MAX_MATCH min_max;
        minMaxLoc(result, &min_max.min_val, &min_max.max_val, &min_max.min_loc, &min_max.max_loc);

        if (min_max.max_val > max_value_aux_par) {
            max_value_aux_par = min_max.max_val;
            size_aux = i;
        }

        #pragma omp critical
        {
            if (max_value_aux_par > max_value_aux) {
                max_value_aux = max_value_aux_par;
                size = size_aux;
            }
        }
    }    
    
    return size;
}

void drawBox(int size, Mat_<FLT> quadrado, Mat_<COR> next_frame_flt) {
    Mat_<FLT> templ = quadrado;
    resize(templ, templ, Size(size, size), 0, 0, INTER_AREA);
    line(next_frame_flt, Point(min_max.match_loc.x + templ.cols / 2, min_max.match_loc.y + templ.rows / 2 + 0.02 * templ.rows), Point(min_max.match_loc.x + templ.cols / 2, min_max.match_loc.y + templ.rows / 2 - 0.02 * templ.rows), Scalar(0, 255, 255), 1, 8);
    line(next_frame_flt,Point(min_max.match_loc.x + templ.cols / 2 + 0.02 * templ.rows, min_max.match_loc.y + templ.rows / 2),Point(min_max.match_loc.x + templ.cols / 2 - 0.02 * templ.rows, min_max.match_loc.y + templ.rows / 2),Scalar(0, 255, 255), 1, 8);
    rectangle(next_frame_flt, min_max.match_loc, Point(min_max.match_loc.x + templ.cols, min_max.match_loc.y + templ.rows), Scalar(0, 255, 255), 1.5, 8);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Utilização do programa:" << "\n";
        std::cout << "cliente4 <ip> [videosaida.avi] [t/c]" << "\n";
        std::cout << "" << std::endl;

        return 0;
    }

    std::string quadrado_file = "quadrado.png";
    std::string output_file = argv[2];
    bool recording = false;
    if (argv[3][0] == 't') {
        recording = true;
    }
    connection::CLIENT client(argv[1]);

    Mat_<COR> received_image;
    Mat_<COR> output;


    // leitura do quadrado
    Mat_<FLT> quadrado;
    le(quadrado, quadrado_file);

    int ch;

    // le primeiro frame do video
    Mat_<COR> next_frame;
    Mat_<FLT> next_frame_flt;
    cv::Point mid_frame;
    cv::Point mid_quadrado;
    uint32_t dist;
    uint32_t positive; // 1 = esquerda, 0 direita
    uint32_t command = 0; // 0 = para, 1 = anda

    // video de saida
    VideoWriter vo(output_file, CV_FOURCC('X', 'V', 'I', 'D'), 30, Size(320, 240));
    int next_size = 0; int last_size = 0;
    do {
        client.receiveImgComp(received_image);
        client.sendUint(1); // recebido

        if (recording) {
            vo << received_image;
        }
        ch = waitKey(25);
        ch = ch % 256;
        if (ch == 27)          // Se esc foi apertado
          client.sendUint(27); // envia 27
        else
          client.sendUint(26); // senao envia 26

        next_frame = received_image.clone();
        flip(next_frame, next_frame, -1);
        converte(next_frame, next_frame_flt);
        quadrado = trataModelo(quadrado, 0.9);

        next_size = bestTemplateSize(0, quadrado, next_frame_flt);
        Mat_<FLT> quadrado_temp;
        resize(quadrado, quadrado_temp, Size(next_size, next_size), 0, 0, INTER_AREA);
        quadrado_temp = somaAbsDois(dcReject(quadrado_temp, 1.0));

        matchTemplate(next_frame_flt, quadrado_temp, result, CV_TM_CCORR);

        minMaxLoc(result, &min_max.min_val, &min_max.max_val, &min_max.min_loc, &min_max.max_loc);
        if (min_max.max_val > 0.18) {
            resize(quadrado, quadrado_temp, Size(next_size, next_size), 0, 0, INTER_AREA);
            matchTemplate(next_frame_flt, quadrado_temp, result_normed, CV_TM_CCOEFF_NORMED);
            minMaxLoc(result_normed, &min_max_normed.min_val, &min_max_normed.max_val, &min_max_normed.min_loc, &min_max_normed.max_loc);
            if ((pow((min_max.max_loc.x - min_max_normed.max_loc.x), 2) + pow((min_max.max_loc.y - min_max_normed.max_loc.y), 2)) < 400 && min_max_normed.max_val > 0.7) {
                if (min_max.max_val > min_max_normed.max_val) {
                    min_max.match_loc = min_max.max_loc;
                } else {
                    min_max.match_loc = min_max_normed.max_loc;
                }
                drawBox(next_size, quadrado, next_frame);
                if ((320 - min_max.match_loc.x) > 40 && (320 - min_max.match_loc.x) < 280) {
                    command = 1;
                }
            }
        } else {
            command = 0;
        }
        flip(next_frame, next_frame, -1);
        vo << next_frame;
        mid_frame = Point(next_frame.cols / 2, next_frame.rows / 2);
        //mid_quadrado = Point(min_max.match_loc.x + quadrado.cols / 2 + 0.02 * quadrado.rows, min_max.match_loc.y + quadrado.rows / 2);
        mid_quadrado = Point((min_max.match_loc.x + quadrado.cols) / 2, (min_max.match_loc.y + quadrado.rows) / 2);
        std::cout << "mid_frame: " << mid_frame.x << ", mid_quadrado: " << mid_quadrado.x << "\r" << std::flush;
        if (mid_quadrado.x > mid_frame.x) {
            positive = 0;
        } else {
            positive = 1;
        }
        dist = static_cast<uint32_t>(std::abs(mid_quadrado.x - mid_frame.x));
        client.sendUint(command);
        client.sendUint(dist);
        client.sendUint(positive);
        imshow("janela", next_frame);

    } while (ch != 27);
    return 0;
}