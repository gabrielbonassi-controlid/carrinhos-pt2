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

int best_template_size(int last_size, Mat_<FLT> img_ref, Mat_<FLT> next_frame_flt) {
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
    for (int i = min; i < max; i = i + 5) { // pula de 5 em 5 pxl pq ngm merece
        resize(img_ref, img_ref_temp, Size(i, i), 0, 0, INTER_AREA);
        img_ref_temp = somaAbsDois(dcReject(img_ref_temp, 1.0));
        matchTemplate(next_frame_flt, img_ref_temp, result, CV_TM_CCOEFF_NORMED);
        minMaxLoc(result, &min_max.min_val, &min_max.max_val, &min_max.min_loc, &min_max.max_loc);
        if (min_max.max_val > max_value_aux) {
            max_value_aux = min_max.max_val;
            size = i;
        }
    }    
    
    return size;
}

void draw_box(int size, Mat_<FLT> quadrado, Mat_<COR> next_frame_flt) {
    Mat_<FLT> templ = quadrado;
    resize(templ, templ, Size(size, size), 0, 0, INTER_AREA);
    line(next_frame_flt, Point(min_max.match_loc.x + templ.cols / 2, min_max.match_loc.y + templ.rows / 2 + 0.02 * templ.rows), Point(min_max.match_loc.x + templ.cols / 2, min_max.match_loc.y + templ.rows / 2 - 0.02 * templ.rows), Scalar(0, 255, 255), 1, 8);
    line(next_frame_flt,Point(min_max.match_loc.x + templ.cols / 2 + 0.02 * templ.rows, min_max.match_loc.y + templ.rows / 2),Point(min_max.match_loc.x + templ.cols / 2 - 0.02 * templ.rows, min_max.match_loc.y + templ.rows / 2),Scalar(0, 255, 255), 1, 8);
    rectangle(next_frame_flt, min_max.match_loc, Point(min_max.match_loc.x + templ.cols, min_max.match_loc.y + templ.rows), Scalar(0, 255, 255), 1.5, 8);
}

int main(int argc, char* argv[]) {
    omp_set_num_threads(4);
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
    Mat_<COR> next_frame_loop;
    if (!vi.read(next_frame)) {
        std::cout << "Não há frames no vídeo" << std::endl;
        return 0;
    }

    // video de saida
    VideoWriter vo(output_file, CV_FOURCC('X', 'V', 'I', 'D'), fps, Size(nc, nl));
    int next_size = 0; int last_size = 0;
    bool is_last_frame = false;
    for (int i=1; i<=frames; i++) {
        std::cout << "Frame no: " << i << "\r" << std::flush;
        vi >> next_frame_loop;

        for (int l=0; l<next_frame_loop.rows; l++) {
            for (int c=0; c<next_frame_loop.cols; c++) {
                next_frame(l,c) = next_frame_loop(l,c);
            }
        }

        converte(next_frame, next_frame_flt);
        quadrado = trataModelo(quadrado, 0.9);

        if (is_last_frame == true) {
            next_size = best_template_size(last_size, quadrado, next_frame_flt);
        } else {
            next_size = best_template_size(0, quadrado, next_frame_flt);
        }

        last_size = next_size;
        Mat_<FLT> quadrado_temp;
        resize(quadrado, quadrado_temp, Size(next_size, next_size), 0, 0, INTER_AREA);
        quadrado_temp = somaAbsDois(dcReject(quadrado_temp, 1.0));

        matchTemplate(next_frame_flt, quadrado_temp, result, CV_TM_CCORR);

        minMaxLoc(result, &min_max.min_val, &min_max.max_val, &min_max.min_loc, &min_max.max_loc);
        if (is_last_frame == true) {
            if (pow((min_max.max_loc.x - min_max.last_loc.x), 2) + pow((min_max.max_loc.y - min_max.last_loc.y), 2) < 400 && min_max.max_val > 0.10) {
                resize(quadrado, quadrado_temp, Size(next_size, next_size), 0, 0, INTER_AREA);
                matchTemplate(next_frame_flt, quadrado_temp, result_normed, CV_TM_CCOEFF_NORMED);
                minMaxLoc(result_normed, &min_max_normed.min_val, &min_max_normed.max_val, &min_max_normed.min_loc, &min_max_normed.max_loc);

                if ((pow((min_max.max_loc.x - min_max_normed.max_loc.x), 2) + pow((min_max.max_loc.y - min_max_normed.max_loc.y), 2)) < 400 && min_max_normed.max_val > 0.10) {
                    if (min_max.max_val > min_max_normed.max_val) {
                        min_max.match_loc = min_max.max_loc;
                    } else {
                        min_max.match_loc = min_max_normed.max_loc;
                    }

                    is_last_frame = true;
                    min_max.last_loc = min_max.match_loc;
                    draw_box(next_size, quadrado, next_frame_loop);
                } else {
                    is_last_frame = false;
                }
            } else {
                is_last_frame = false;
            } 
        } else {
            if (min_max.max_val > 0.18) {
                resize(quadrado, quadrado_temp, Size(next_size, next_size), 0, 0, INTER_AREA);
                matchTemplate(next_frame_flt, quadrado_temp, result_normed, CV_TM_CCOEFF_NORMED);
                minMaxLoc(result_normed, &min_max_normed.min_val, &min_max_normed.max_val, &min_max_normed.min_loc, &min_max_normed.max_loc);

                if ((pow((min_max.max_loc.x - min_max_normed.max_loc.x), 2) + pow((min_max.max_loc.y - min_max_normed.max_loc.y), 2)) < 400 && min_max_normed.max_val > 0.18) {
                    if (min_max.max_val > min_max_normed.max_val) {
                        min_max.match_loc = min_max.max_loc;
                    } else {
                        min_max.match_loc = min_max_normed.max_loc;
                    }

                    is_last_frame = true;
                    min_max.last_loc = min_max.match_loc;
                    draw_box(next_size, quadrado, next_frame_loop);
                } else {
                    is_last_frame = false;
                }
            } else {
                is_last_frame = false;
            }
        }
        vo << next_frame_loop;
        for (int n=0; n<=i; n++) {
            std::cout << "\b";
            std::cout << " ";
        }
    }
    TimePoint t2 = timePoint();
    double fps_total = frames / timeSpan(t1, t2);
    std::cout << "FPS total: " << fps_total << "\n";
    std::cout << "Tempo total: " << timeSpan(t1, t2) << std::endl;
    return 0;
}