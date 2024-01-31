#include <cekeikon.h>

#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

using namespace std;

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
    int size= 100;
    int min = 30;
    int max = 130;
    float max_value_aux = 0.0;
    Mat_<FLT> img_ref_temp;

    if (last_size < 15) {
        min = 15;
        max = 70;
    } else {
        min = last_size - 10;
        max = last_size + 10;
    }
#pragma omp parallel for
    for (int i = min; i < max; i = i + 5) {
        Mat_<FLT> img_ref_temp, result;
        double max_value_aux_par = -1;
        int size_aux = -1;

        resize(img_ref, img_ref_temp, Size(i, i), 0, 0, INTER_AREA);
        img_ref_temp = somaAbsDois(dcReject(img_ref_temp, 1.0));
        matchTemplate(next_frame_flt, img_ref_temp, result, CV_TM_CCORR);

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
    line(next_frame_flt, Point(min_max.match_loc.x + templ.cols / 2 + 0.02 * templ.rows, min_max.match_loc.y + templ.rows / 2),Point(min_max.match_loc.x + templ.cols / 2 - 0.02 * templ.rows, min_max.match_loc.y + templ.rows / 2),Scalar(0, 255, 255), 1, 8);
    rectangle(next_frame_flt, min_max.match_loc, Point(min_max.match_loc.x + templ.cols, min_max.match_loc.y + templ.rows), Scalar(0, 255, 255), 1.5, 8);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Utilização do programa:" << "\n";
        std::cout << "fase3 video_capturado.avi quadrado.png video_localizando.avi" << "\n";
        std::cout << "" << std::endl;

        return 0;
    }
    TimePoint t1=timePoint();

    std::string video_file = argv[1];
    std::string quadrado_file = argv[2];
    std::string output_file = argv[3];


    // leitura do quadrado
    Mat_<FLT> quadrado;
    le(quadrado, quadrado_file);
    
    // leitura do video
    VideoCapture vi(video_file);
    // infos do video
    float fps = vi.get(CV_CAP_PROP_FPS);
    std::cout << "FPS original do video: " << fps << "\n";
    int nc = vi.get(CV_CAP_PROP_FRAME_WIDTH);
    int nl = vi.get(CV_CAP_PROP_FRAME_HEIGHT);
    std::cout << "Resolução do video: " << nc << "x" << nl << "\n";
    int frames = vi.get(CV_CAP_PROP_FRAME_COUNT);
    std::cout << "Numero de frames do video: " << frames << "\n";

    // le primeiro frame do video
    Mat_<COR> next_frame;
    Mat_<FLT> next_frame_flt;
    if (!vi.read(next_frame)) {
        std::cout << "Não há frames no vídeo" << std::endl;
        return 0;
    }

    // janela exibindo o resultado
    namedWindow("Fase 5", CV_WINDOW_AUTOSIZE);

    // mnist
    MNIST mnist(14, true, true);
    mnist.le("/home/gabriel-controlid/poli/carrinhos-pt2/aula-5/mnist");
    flann::Index index(mnist.ax, flann::KDTreeIndexParams(4));

    // video de saida
    VideoWriter vo(output_file, CV_FOURCC('X', 'V', 'I', 'D'), fps, Size(nc + 200, nl));
    int next_size = 0;

    for (int i=1; i<frames; i++) {
        vi >> next_frame;

        if (!next_frame.empty()) {
            converte(next_frame, next_frame_flt);
        }
        quadrado = trataModelo(quadrado, 1.0);

        next_size = bestTemplateSize(0, quadrado, next_frame_flt);
        Mat_<FLT> quadrado_temp;
        resize(quadrado, quadrado_temp, Size(next_size, next_size), 0, 0, INTER_AREA);
        quadrado_temp = somaAbsDois(dcReject(quadrado_temp));

        matchTemplate(next_frame_flt, quadrado_temp, result, CV_TM_CCORR);

        minMaxLoc(result, &min_max.min_val, &min_max.max_val, &min_max.min_loc, &min_max.max_loc);
        if (min_max.max_val > 0.2) {
            resize(quadrado, quadrado_temp, Size(next_size, next_size), 0, 0, INTER_AREA);
            matchTemplate(next_frame_flt, quadrado_temp, result_normed, CV_TM_CCOEFF_NORMED);
            minMaxLoc(result_normed, &min_max_normed.min_val, &min_max_normed.max_val, &min_max_normed.min_loc, &min_max_normed.max_loc);
            if ((pow((min_max.max_loc.x - min_max_normed.max_loc.x), 2) + pow((min_max.max_loc.y - min_max_normed.max_loc.y), 2)) < 400 && min_max_normed.max_val > 0.5) {
                if (min_max.max_val > min_max_normed.max_val) {
                    min_max.match_loc = min_max.max_loc;
                } else {
                    min_max.match_loc = min_max_normed.max_loc;
                }
                min_max.last_loc = min_max.match_loc;
                drawBox(next_size, quadrado, next_frame);
            }
        }
        int cut = next_size * 0.4;
        int border = next_size * (1 - 0.4);
        Mat_<FLT> number(cut, cut);
        Mat_<FLT> number_big;
        Mat_<COR> number_color;
        Mat_<FLT> qx2(1, 14*14);
        Mat_<FLT> number_14;
        Mat_<COR> number_14_color;
        for (int l = 0; l < cut; l++) {
            for (int c = 0; c < cut; c++) {
                number(l, c) = next_frame_flt(min_max.max_loc.y + l + border/2, min_max.max_loc.x + c + border/2);
            }
        }

        resize(number, number_14, Size(14, 14), 0, 0, INTER_AREA);
        converte(number_14, number_14_color);
        int left, right, top, bottom;
        bool localized;
        left = number_14.cols;
        right = 0;
        top = number_14.rows;
        bottom = 0;

        for (int l = 0; l < number_14.rows; l++) {
            for (int c = 0; c < number_14.cols; c++) {
                if (number_14(l, c) < 0.5) {
                    number_14(l, c) = 0;
                } else {
                    number_14(l, c) = 1;
                }

                if (number_14(l, c) != 1) {
                    if (c < left) {
                        left = c;
                    }
                    if (c > right) {
                        right = c;
                    }
                    if (l < top) {
                        top = l;
                    }
                    if (l > bottom) {
                        bottom = l;
                    }
                }
            }
        }

        Mat_<FLT> d;
        Mat_<FLT> d_big;
        if (!(left < right && top < bottom)) {
            localized = false;
            d.create(14, 14);
            d.setTo(128);
        } else {
            localized = true;
            Mat_<FLT> roi(number_14, Rect(left, top, right - left + 1, bottom - top + 1));
            resize(roi, d, Size(14, 14), 0, 0, INTER_AREA);
        }

        for (int l = 0; l < d.rows; l++) {
            for (int c = 0; c < d.cols; c++) {
                qx2(0, l * number_14.cols + c) = d(l, c);
            }
        }
        int result_recon;
        std::vector<int> indexes(1);
        std::vector<float> dists(1);
        index.knnSearch(qx2, indexes, dists, 1);
        result_recon = mnist.ay(indexes[0]);
        std::cout << "Frame no: " << i << ", localizou: " << localized << ", qp:" << result_recon << "\r" << std::flush;
        resize(d, number_big, Size(200, 200), 0, 0, INTER_AREA);
        Mat_<COR> out;
        Mat_<COR> number_big_color;
        if (!number_big.empty()){
            converte(number_big, number_big_color);
        }
        out = grudaH(next_frame, number_big_color);
        if (min_max.max_val > 0.2 && min_max_normed.max_val > 0.5) {
            putText(out, to_string(result_recon), Point(min_max.max_loc.x + next_size / 2, min_max.max_loc.y + next_size / 2), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255));
        } else {
            for (int c = 0; c < d_big.cols; c++) {
                for (int l = 0; l < d_big.rows; l++) {
                    d(l, c) = 0;
                }
            }
        }
        resize(d, d_big, Size(200, 200), 0, 0, INTER_AREA);
        imshow("Fase 5", out);
        vo << out;
        cv::waitKey(1);
    }
    TimePoint t2 = timePoint();
    double fps_total = frames / timeSpan(t1, t2);
    std::cout << "\n" << "FPS total: " << fps_total << "\n";
    std::cout << "Tempo total: " << timeSpan(t1, t2) << std::endl;
}